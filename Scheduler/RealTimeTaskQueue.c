#pragma once

#include <stdlib.h>
#include "consts.h"
#include "logger.h"
#include "RealTimeTaskQueue.h"


void push_task_node(struct real_time_task_queue* real_time_task_queue, struct queue_node* real_time_node) {
    // Check if the queue or node is NULL and log an error
    if (real_time_task_queue == NULL) {
        char mess[STANDART_SIZE_MESS];
        ERROR_MESSAGE_QUEUE_NOT_INITIALIZED(mess);
        LOG_ERROR(mess);
        return;
    }

    if (real_time_node == NULL) {
        char mess[STANDART_SIZE_MESS];
        ERROR_MESSAGE_ACCESSING_NULL_POINTER(mess);
        LOG_ERROR(mess);
        return;
    }

    // Insert the new node at the end of the queue
    if (real_time_task_queue->rear) {
        real_time_task_queue->rear->next = real_time_node;
    }
    else {
        real_time_task_queue->front = real_time_node;
    }
    real_time_task_queue->rear = real_time_node;
    real_time_task_queue->num_of_tasks++;
    real_time_task_queue->total_weights += real_time_node->task->weight;

    // Log an info message about the new task insertion
    char mess[STANDART_SIZE_MESS];
    INFO_MESSAGE_NEW_TASK_INSERT_TO_QUEUE(mess, real_time_node->task->id, real_time_node->task->remaining_time);
    LOG_INFO(mess);
}

struct queue_node* pop_task_node(struct real_time_task_queue* real_time_task_queue) {
    if (real_time_task_queue == NULL) {
        char mess[STANDART_SIZE_MESS];
        ERROR_MESSAGE_QUEUE_NOT_INITIALIZED(mess);
        LOG_ERROR(mess);
        return NULL;
    }

    if (real_time_task_queue->front == NULL) {
        char mess[STANDART_SIZE_MESS];
        ERROR_MESSAGE_QUEUE_EMPTY(mess);
        LOG_ERROR(mess);
        return NULL;
    }

    struct queue_node* queue_node = real_time_task_queue->front;
    real_time_task_queue->front = real_time_task_queue->front->next;
    if (!real_time_task_queue->front) {
        real_time_task_queue->rear = NULL;
    }

    real_time_task_queue->num_of_tasks--;
    real_time_task_queue->total_weights -= queue_node->task->weight;
    queue_node->next = NULL;

    // Log an info message about the task removal
    char mess[STANDART_SIZE_MESS];
    INFO_MESSAGE_TASK_REMOVED_FROM_QUEUE(mess, queue_node->task->id);
    LOG_INFO(mess);

    return queue_node;
}

int is_queue_empty(struct real_time_task_queue* real_time_task_queue) {
    if (real_time_task_queue == NULL) {
        char mess[STANDART_SIZE_MESS];
        ERROR_MESSAGE_ACCESSING_NULL_POINTER(mess);
        LOG_ERROR(mess);
        return 1; // Consider the queue empty if it’s not initialized
    }
    return real_time_task_queue->front == NULL;
}
