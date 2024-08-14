#include "rb_node.h"

rb_node* create_rb_node(task* task) {

	if (task == NULL) {

	}
	//create new rb node 
	rb_node* node = (rb_node*)malloc(sizeof(rb_node));
	if (node == NULL) {
		//Alocation failed
		exit(1);
	}
	node->task = task;
	node->parent = node->left = node->right = NULL;

	return node;
}

void free_rb_node(rb_node* node) {
	if (node != NULL) {
		free_task(node->task);
		free(node);
	}
}