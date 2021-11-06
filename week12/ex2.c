#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>

#define PRESSED "PRESSED 0x%X (%d)\n"
#define REALEASED "REALEASED 0x%X (%d)\n"
#define REPEAT "REPEAT 0x%X (%d)\n"

// should run under sudo

int main(){
	FILE *f = fopen("/dev/input/by-path/platform-i8042-serio-0-event-kbd", "r");

	struct timeval last = {0, 0};

	while (1){
		struct input_event e;
		fread(&e, sizeof(struct input_event), 1, f);
		
		// non relevant event types
		if (e.type != EV_KEY)
			continue;
		
		// remove read character from terminal window
		printf("\033[1D");

		if (e.value == 0)
			printf(REALEASED, e.code, e.code);
		else if (e.value == 1)
			printf(PRESSED, e.code, e.code);
		else
			printf(REPEAT, e.code, e.code);

		last = e.time;
	}
}