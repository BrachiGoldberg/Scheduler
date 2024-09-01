#include "rb_node.h"
#include "logger.h"
#include "consts.h"

rb_node* create_rb_node(task* task) {

	//does it unnecessary???
	//if (task == NULL) {
	//	LOG_ERROR(ACCESSING_NULL_PIONTER);
	//	//exit?????????
	//}

	//create new rb node 
	rb_node* node = (rb_node*)malloc(sizeof(rb_node));
	if (node == NULL) {
		//Alocation failed
		LOG_ERROR(MEMORY_ALLOCATION_FAILED);
		exit(1);
	}
	node->task = task;
	node->parent = node->left = node->right = NULL;

	return node;
}

void free_rb_node(rb_node* node) {
	if (node == NULL)
		LOG_ERROR(ACCESSING_NULL_PIONTER);
	else {
		free_task(node->task);
		free(node);
	}
	node == NULL;
}