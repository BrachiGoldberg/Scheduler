#define STANDART_SIZE_MESS 256

// î÷øåàéí ìäåãòåú îéãò
#define INFO_MESSAGE_NEW_TASK_INSERT_TO_QUEUE(mess, task_id, exec_time) \
    snprintf((mess), STANDART_SIZE_MESS, "New task number %ld with %f execution time was inserted to the real-time tasks queue", (task_id), (exec_time))

#define INFO_MESSAGE_NEW_TASK_INSERT_TO_RB_TREE(mess, task_id, exec_time) \
    snprintf((mess), STANDART_SIZE_MESS, "New task number %ld with %f execution time was inserted to the red-black tree", (task_id), (exec_time))

#define INFO_MESSAGE_TASK_GET_CPU(mess, task_id, time) \
    snprintf((mess), STANDART_SIZE_MESS, "Task number %ld got the CPU for %f milliseconds", (task_id), (time))

#define INFO_MESSAGE_TASK_FINISHED(mess, task_id) \
    snprintf((mess), STANDART_SIZE_MESS, "Task number %ld finished", (task_id))

#define INFO_MESSAGE_TASK_REMOVED_FROM_QUEUE(mess, task_id) \
    snprintf((mess), STANDART_SIZE_MESS, "Task number %ld removed from the real-time tasks queue", (task_id))


//macros for debug messages
#define DEBUG_MESSAGE_TASK_SCHEDULED(mess, task_id, exec_time) \
    snprintf((mess), STANDART_SIZE_MESS, "Task number %ld scheduled with %f milliseconds", (task_id), (exec_time))

// î÷øåàéí ìùâéàåú
#define ERROR_MESSAGE_MEMORY_ALLOCATION_FAILED "Memory allocation failed"

#define ERROR_MESSAGE_ACCESSING_NULL_POINTER "Accessing a null pointer"

#define ERROR_MESSAGE_QUEUE_NOT_INITIALIZED "The queue was not initialized"

#define ERROR_MESSAGE_TREE_NOT_INITIALIZED "The red-black tree was not initialized"

#define ERROR_MESSAGE_QUEUE_EMPTY "The queue is empty of tasks"

#define ERROR_MESSAGE_TREE_EMPTY "The tree is empty of tasks"

#define ERROR_MESSAGE_CREATE_TREE_MUTEX_FAILED "Failed to create tree mutex"

#define ERROR_MESSAGE_LOCK_TREE_MUTEX_FAILED "Failed to lock tree mutex"

#define ERROR_MESSAGE_UNLOCK_TREE_MUTEX_FAILED "Failed to unlock tree mutex"

#define ERROR_MESSAGE_CREATE_QUEUE_MUTEX_FAILED "Failed to create queue mutex"

#define ERROR_MESSAGE_LOCK_QUEUE_MUTEX_FAILED "Failed to lock tree mutex"

#define ERROR_MESSAGE_UNLOCK_QUEUE_MUTEX_FAILED "Failed to unlock tree mutex"

// ìåâ ùâéàåú
//#define LOG_ERROR(msg) fprintf(stderr, "%s\n", (msg))
