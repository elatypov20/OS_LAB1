#include <stdio.h>

#define ARR_SIZE(x)  (sizeof(x) / sizeof((x)[0])) 

struct node {
	struct node *next;
	int value;
};

// function prototypes
void print_list(struct node *head);
void insert_node(struct node *head, struct node *newnode, struct node *prevnode);
void delete_node(struct node *head, struct node *delnode);

int main() {
	struct node initial[] = {
		{.value = 10, .next = NULL},
		{.value = 20, .next = NULL},
		{.value = 30, .next = NULL},
		{.value = 40, .next = NULL},
	};

	struct node *head = &initial[0];

	for (int i = 1; i < ARR_SIZE(initial); ++i) {
		insert_node(head, &initial[i], &initial[i - 1]);
	}

	printf("Initial structure:\n");
	print_list(head);

	struct node node1 = {.value = 500, .next = NULL};
	insert_node(head, &node1, &initial[2]);
	printf("Insert node after node3:\n");
	print_list(head);

	delete_node(head, &initial[1]);
	printf("Delete node2:\n");
	print_list(head);
}


void print_list(struct node *head) {
	do {
		printf("%d\n", head->value);
	} while ((head = head->next) != NULL);
}

void insert_node(struct node *head, struct node *newnode, struct node *prevnode) {
	struct node *new_next = prevnode->next;
	prevnode->next = newnode;
	newnode->next = new_next;
}

void delete_node(struct node *head, struct node *delnode) {
	struct node *prevnode;

	while (head->next != delnode){
		head = head->next;
	}
	prevnode = head;

	struct node *new_next = delnode->next;
	prevnode->next = new_next;
}