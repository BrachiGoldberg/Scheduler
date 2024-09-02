#include "rb_node.h"

rb_node* create_rb_node(task* task) {
    // Check if task is NULL and log an error if necessary
    if (task == NULL) {
        LOG_ERROR(ERROR_MESSAGE_ACCESSING_NULL_POINTER);
        // Optionally handle the error, e.g., by returning NULL
        return NULL;
    }

    // Create new rb node
    rb_node* node = (rb_node*)malloc(sizeof(rb_node));
    if (node == NULL) {
        LOG_ERROR(ERROR_MESSAGE_MEMORY_ALLOCATION_FAILED);
        exit(EXIT_FAILURE); // Use a standard exit code
    }
    node->task = task;
    node->parent = node->left = node->right = NULL;

    return node;
}

void free_rb_node(rb_node* node) {
    if (node == NULL) {
        LOG_ERROR(ERROR_MESSAGE_ACCESSING_NULL_POINTER);
        return;
    }

    free_task(node->task);
    free(node);
    // Setting node to NULL is unnecessary as it’s not used after this
}
