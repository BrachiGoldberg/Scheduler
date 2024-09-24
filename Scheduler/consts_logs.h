#ifndef CONSTS_LOGS_H
#define CONSTS_LOGS_H

#define STANDART_SIZE_MESS 256
//macros of trace messages
#define TRACE_MESSAGE_EXECUTE_REAL_TIME_TASK "Execute real-time task (form the queue)"

//macros of info messages
#define INFO_MESSAGE_TASK_INSERT_TO_QUEUE(mess, task_id, exec_time) \
    snprintf((mess), STANDART_SIZE_MESS, "Task number %ld with %f execution time was inserted to the real-time tasks queue", (task_id), (exec_time))

#define INFO_MESSAGE_TASK_INSERT_TO_RB_TREE(mess, task_id, exec_time) \
    snprintf((mess), STANDART_SIZE_MESS, "Task number %ld with %f execution time was inserted to the red-black tree", (task_id), (exec_time))

#define INFO_MESSAGE_TASK_GET_CPU(mess, task_id, time) \
    snprintf((mess), STANDART_SIZE_MESS, "Task number %ld got the CPU for %f milliseconds", (task_id), (time))

#define INFO_MESSAGE_TASK_FINISHED(mess, task_id) \
    snprintf((mess), STANDART_SIZE_MESS, "Task number %ld finished", (task_id))

#define INFO_MESSAGE_TASK_REMOVED_FROM_QUEUE(mess, task_id) \
    snprintf((mess), STANDART_SIZE_MESS, "Task number %ld removed from the real-time tasks queue", (task_id))

#define INFO_MESSAGE_CREATED_NEW_REAL_TIME_TASK(mess, task_id, exec_time,weight) \
    snprintf((mess), STANDART_SIZE_MESS, "Created new real-time task ID %ld with execution time %f and weight %Lf", (task_id), (exec_time),(weight))

#define INFO_MESSAGE_CREATED_NEW_TASK(mess, task_id, exec_time,weight) \
    snprintf((mess), STANDART_SIZE_MESS, "Created new task ID %ld with execution time %f and weight %Lf", (task_id), (exec_time),(weight))

#define INFO_MESSAGE_FREEING_REAL_TIME_TASK(mess, task_id) \
    snprintf((mess), STANDART_SIZE_MESS, "Freeing real-time task ID %ld", (task_id))

#define INFO_MESSAGE_FREEING_TASK(mess, task_id) \
    snprintf((mess), STANDART_SIZE_MESS, "Freeing task ID %ld", (task_id))

#define INFO_MESSAGE_QUEUE_GOT_CPU(mess, acount) \
    snprintf((mess), STANDART_SIZE_MESS, "%d tasks from the queue got the CPU in the current round", (acount))

#define INFO_MESSAGE_TREE_GOT_CPU(mess, acount) \
    snprintf((mess), STANDART_SIZE_MESS, "%d tasks from the tree got the CPU in the current round", (acount))

#define INFO_MESSAGE_START_SECHEDULING_TASKS "Starting task scheduling process"

#define INFO_MESSAGE_TREE_INITIALIZED "The red-black tree was initialized"

#define INFO_MESSAGE_QUEUE_INITIALIZED "The queue was initialized"

//macros of debug messages
#define DEBUG_MESSAGE_TASK_SCHEDULED(mess, task_id, exec_time) \
    snprintf((mess), STANDART_SIZE_MESS, "Task number %ld scheduled with %f milliseconds", (task_id), (exec_time))

#define DEBUG_MESSAGE_CALCULATE_QUANTUM(mess, task_id, quantum) \
    snprintf((mess), STANDART_SIZE_MESS, "Calculated quantum: %f for task ID: %d", quantum, task_id)

#define DEBUG_MESSAGE_ROTATION_SKIPPED_FATHER_NULL "Rotation skipped as parent of node is NULL"

#define DEBUG_MESSAGE_ROTATION_SKIPPED_GRANDPARENT_NULL "Rotation skipped as the grandparent of the node is NULL"

#define DEBUG_MESSAGE_NO_TASKS_AVAILABLE "No task available thread go to slepp:)..."

#define DEBUG_MESSAGE_EXECUTE_THREAD_WOKE_UP "GOOD MORNING I AM AWAKE"
//macors 0f error messages
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

#define ERROR_MESSAGE_LOGGER_INIT_FAILED "ERROR! init logger file failed"

#define ERROR_MESSAGE_CREATE_TASK_TREAD_FAILED "Failed to create task thread"

#define ERROR_MESSAGE_CREATE_INPUT_TREAD_FAILED "Failed to create input thread"

#endif // !CONSTS_LOGS_H