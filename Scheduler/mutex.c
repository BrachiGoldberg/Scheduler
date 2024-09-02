#include "mutex.h"

//create tree mutex
void create_tree_mutex() {
    tree_mutex = CreateMutex(NULL, FALSE, NULL);
    if (tree_mutex == NULL) {
        // Handle error
        LOG_ERROR(ERROR_MESSAGE_CREATE_TREE_MUTEX_FAILED);
    }
}

//lock tree mutex
void lock_tree_mutex() {
    DWORD dwWaitResult = WaitForSingleObject(tree_mutex, INFINITE);
    if (dwWaitResult != WAIT_OBJECT_0) {
        // Handle error
        LOG_ERROR(ERROR_MESSAGE_LOCK_TREE_MUTEX_FAILED);
    }
}

//unlock tree mutex
void release_tree_mutex() {
    if (!ReleaseMutex(tree_mutex)) {
        // Handle error
        LOG_ERROR(ERROR_MESSAGE_UNLOCK_TREE_MUTEX_FAILED);
    }
}

//create queue mutex
void create_queue_mutex() {
    queue_mutex = CreateMutex(NULL, FALSE, NULL);
    if (queue_mutex == NULL) {
        // Handle error
        LOG_ERROR(ERROR_MESSAGE_CREATE_QUEUE_MUTEX_FAILED);
    }
}

//lock queue mutex
void lock_queue_mutex() {
    DWORD dwWaitResult = WaitForSingleObject(queue_mutex, INFINITE);
    if (dwWaitResult != WAIT_OBJECT_0) {
        // Handle error
        LOG_ERROR(ERROR_MESSAGE_LOCK_QUEUE_MUTEX_FAILED);
    }
}

//unlock queue mutex
void release_queue_mutex() {
    if (!ReleaseMutex(queue_mutex)) {
        // Handle error
        LOG_ERROR(ERROR_MESSAGE_UNLOCK_QUEUE_MUTEX_FAILED);
    }
}
