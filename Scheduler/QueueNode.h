#pragma once
#include "RealTimeTask.h"

struct queue_node {
	struct real_time_task* task;
	struct queue_node* next;
};

struct queue_node* create_queue_node(int priority, double execution_time, long double weight);
void free_queue_node(struct queue_node* node);