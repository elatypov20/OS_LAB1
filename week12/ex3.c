#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <string.h>
#include <stdlib.h>

#define PRESSED "PRESSED 0x%X (%d)\n"
#define REALEASED "REALEASED 0x%X (%d)\n"
#define REPEAT "REPEAT 0x%X (%d)\n"

#define KEY_RELEASED 0
#define KEY_PRESSED 1
#define KEY_REPEAT 2

// this array will store state of each key

struct shortcut_handler{
	char *shortcut;
	void (*handler)();
};

void add_shortcut_handler(struct shortcut_handler hdl);
void update_states();

// handlers
void PE_handler();
void CAP_handler();
void ZXC_handler();

char key_states[512];
struct timeval timestamps[512];

char num_handlers = 0;
struct shortcut_handler *handlers = NULL;
 
// should run under sudo
int main(){
	memset(key_states, KEY_RELEASED, 512);

	// register handlers
	char pe_shortcut[] = {0x19, 0x12, 0};
	char cap_shortcut[] = {0x2E, 0x1E, 0x19, 0};
	char zxc_shortcut[] = {0x2C, 0x2D, 0x2E, 0};

	struct shortcut_handler pe_handler = {.shortcut = pe_shortcut, .handler = PE_handler};
	struct shortcut_handler cap_handler = {.shortcut = cap_shortcut, .handler = CAP_handler};
	struct shortcut_handler zxc_handler = {.shortcut = zxc_shortcut, .handler = ZXC_handler};

	add_shortcut_handler(pe_handler);
	add_shortcut_handler(cap_handler);
	add_shortcut_handler(zxc_handler);

	FILE *f = fopen("/dev/input/by-path/platform-i8042-serio-0-event-kbd", "r");

	while (1){
		struct input_event e;
		fread(&e, sizeof(struct input_event), 1, f);
		
		// non relevant event types
		if (e.type != EV_KEY)
			continue;
		
		// remove read character from terminal window
		printf("\033[1D \033[1D");
		fflush(stdout);

		key_states[e.code] = e.value;
		timestamps[e.code] = e.time;

		update_states();
	}
}

void add_shortcut_handler(struct shortcut_handler hdl){
	++num_handlers;
	handlers = (struct shortcut_handler*) realloc(handlers, num_handlers * sizeof(struct shortcut_handler));
	handlers[num_handlers - 1] = hdl;
}

void update_states(){
	for (int i = 0; i < num_handlers; ++i){
		int is_active = 1;
		for (int j = 0; j < strlen(handlers[i].shortcut); ++j){
			if (key_states[handlers[i].shortcut[j]] != KEY_PRESSED){
				is_active = 0;
				break;
			}

			// check sequence
			if (j == 0) continue;

			struct timeval _t1 = timestamps[handlers[i].shortcut[j]];
			struct timeval _t2 = timestamps[handlers[i].shortcut[j - 1]];
			
			long long time_cur = _t1.tv_sec * 1000000000000 + _t1.tv_usec;
			long long time_prev = _t2.tv_sec * 1000000000000 + _t2.tv_usec;

			if (time_prev > time_cur){
				is_active = 0;
				break;
			}
		}

		if (is_active)
			handlers[i].handler();
	}
}


void PE_handler(){
	printf("I passed the Exam!\n");
}

void CAP_handler(){
	printf("Get some cappuccino!\n");
}

void ZXC_handler(){
	printf("I am clown!\n");
}