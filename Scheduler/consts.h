
#define STANDART_SIZE_MESS 256

#define INFO_MESSAGE_NEW_TASK_INSERT_TO_QUEUE(mess, task_id, exec_time) snprintf((mess), "New task number %dl with %d execution time was inserted to the real-time tasks queue", (task_id), (exec_time))
#define INFO_MESSAGE_NEW_TASK_INSERT_TO_RB_TREE(mess, task_id, exec_time) snprintf((mess), "New task number %dl with %d execution time was inserted to the red-black tree", (task_id), (exec_time))

#define INFO_MESSAGE_TASK_GET_CPU(mess, task_id, time) snprintf( (mess),"Task number %dl got the CPU for %d milliseconds",(task_id) ,(time))
#define INFO_MESSAGE_TASK_FINISHED(mess, task_id) snprintf((mess), "Task number %dl finished ", (task_id))


#define MEMORY_ALLOCATION_FAILED "Memory allocation failed"
#define ACCESSING_NULL_PIONTER "Accessing a null pointer"
#define QUEUE_WAS_NOT_INITIALIZED "The queue was not been initialized"
#define TREE_WAS_NOT_INITIALIZED "The red-black tree was not been initialized"