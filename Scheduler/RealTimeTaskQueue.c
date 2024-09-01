#pragma once
#include <stdlib.h>
#include "RealTimeTaskQueue .h"
#include "consts.h"
#include "logger.h"

void push_task_node(struct real_time_task_queue* real_time_task_queue,struct queue_node* real_time_node) {

    //struct queue_node* new_node = create_queue_node(priority, execution_time);
    if (real_time_task_queue->rear) {
        real_time_task_queue->rear->next = real_time_node;
    }
    else {
        real_time_task_queue->front = real_time_node;
    }
    real_time_task_queue->rear = real_time_node;
    real_time_task_queue->num_of_tasks++;
    real_time_task_queue->total_weights += real_time_node->task->weight;

    //info log message
    char mess[STANDART_SIZE_MESS];
    INFO_MESSAGE_NEW_TASK_INSERT_TO_QUEUE(mess,real_time_node->task->id, real_time_node->task->execution_time);
    LOG_INFO(mess);
}

struct queue_node* pop_task_node(struct real_time_task_queue* real_time_task_queue) {
    if (!real_time_task_queue->front) return NULL;
    struct queue_node* queue_node = real_time_task_queue->front;
    queue_node->next = NULL;
    real_time_task_queue->front = real_time_task_queue->front->next;
    if (!real_time_task_queue->front) {
        real_time_task_queue->rear = NULL;
    }
    return queue_node;
}

int is_queue_empty(struct real_time_task_queue* real_time_task_queue) {
    if (!real_time_task_queue->front)
        return 1;
    return 0;
}


