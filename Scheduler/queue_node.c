#include "queue_node.h"

 queue_node* create_queue_node(int priority, double execution_time, long double weight) {
     queue_node* new_queue_node = ( queue_node*)malloc(sizeof( queue_node));
    if (new_queue_node == NULL) {
        LOG_ERROR(ERROR_MESSAGE_MEMORY_ALLOCATION_FAILED);
        exit(EXIT_FAILURE); // Or handle the error as appropriate
    }

    new_queue_node->task = create_real_time_task(priority, execution_time, weight);
    new_queue_node->next = NULL;
    return new_queue_node;
}

void free_queue_node( queue_node* node) {
    if (node == NULL) {
        LOG_ERROR(ERROR_MESSAGE_ACCESSING_NULL_POINTER);
        return;
    }

    free_real_time_task(node->task);
    free(node);
    node = NULL; // Optional, since node is not used after this
}
