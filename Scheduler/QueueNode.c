#pragma once
#include "QueueNode.h"
#include <stdlib.h>

struct queue_node* create_queue_node(int priority, double execution_time, long double weight) {
	struct queue_node* new_queue_node = (struct queue_node*)malloc(sizeof(struct queue_node));
	new_queue_node->task = create_real_time_task(priority, execution_time, weight);
	new_queue_node->next = NULL;
	return new_queue_node;
}
void free_queue_node(struct queue_node* node) {
	free_real_time_task(node->task);
	free(node);
}