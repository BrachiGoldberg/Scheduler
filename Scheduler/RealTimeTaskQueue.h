#pragma once
#include "QueueNode.h"
#include "mutex.h"
//#include "RealTimeTask.h"
// A queue of real-time tasks
struct real_time_task_queue {
    struct queue_node* front; // Head of queue
    struct queue_node* rear; // the tail of the queue
    //initialize at 0!!
    long double total_weights; //total_weights fo all the real timr task in thr queue
    int num_of_tasks; //the count for all the real timr task in thr queue
};

void push_task_node(struct real_time_task_queue* real_time_task_queue, struct queue_node* real_time_node);
struct queue_node* pop_task_node(struct real_time_task_queue* real_time_task_queue);
int is_queue_empty(struct real_time_task_queue* real_time_task_queue);

