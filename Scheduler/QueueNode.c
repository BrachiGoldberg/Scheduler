#pragma once
#include "QueueNode.h"
#include "consts.h"
#include "logger.h"
#include <stdlib.h>

struct queue_node* create_queue_node(int priority, double execution_time, long double weight) {
	struct queue_node* new_queue_node = (struct queue_node*)malloc(sizeof(struct queue_node));
	if (new_queue_node == NULL) {
		//memory allocation failed
		LOG_ERROR(MEMORY_ALLOCATION_FAILED);
		//exit(1)????
	}

	new_queue_node->task = create_real_time_task(priority, execution_time, weight);
	new_queue_node->next = NULL;
	return new_queue_node;
}

void free_queue_node(struct queue_node* node) {
	if (node != NULL) {
		LOG_ERROR(ACCESSING_NULL_PIONTER);
	}
	else {
		free_real_time_task(node->task);
		free(node);
	}
	node = NULL;
}