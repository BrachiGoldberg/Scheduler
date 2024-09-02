#pragma once
#include "QueueNode.h"
#include "consts.h"
#include "logger.h"
#include <stdlib.h>

struct queue_node* create_queue_node(int priority, double execution_time, long double weight) {
    struct queue_node* new_queue_node = (struct queue_node*)malloc(sizeof(struct queue_node));
    if (new_queue_node == NULL) {
        char message[STANDART_SIZE_MESS];
        ERROR_MESSAGE_MEMORY_ALLOCATION_FAILED(message);
        LOG_ERROR(message);
        exit(EXIT_FAILURE); // Or handle the error as appropriate
    }

    new_queue_node->task = create_real_time_task(priority, execution_time, weight);
    new_queue_node->next = NULL;
    return new_queue_node;
}

void free_queue_node(struct queue_node* node) {
    if (node == NULL) {
        char message[STANDART_SIZE_MESS];
        ERROR_MESSAGE_ACCESSING_NULL_POINTER(message);
        LOG_ERROR(message);
        return;
    }

    free_real_time_task(node->task);
    free(node);
    node = NULL; // Optional, since node is not used after this
}
