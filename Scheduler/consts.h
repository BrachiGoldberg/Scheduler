



#define STANDART_SIZE_MESS 256

#define INFO_MESSAGE_NEW_TASK_INSERT_TO_QUEUE(mess, task_id, exec_time) snprintf((mess), "new task number %dl with %d execution time was inserted to the real-time tasks queue", (task_id), (exec_time))
#define INFO_MESSAGE_NEW_TASK_INSERT_TO_RB_TREE(mess, task_id, exec_time) snprintf((mess), "new task number %dl with %d execution time was inserted to the red-black tree", (task_id), (exec_time))

#define INFO_MESSAGE_TASK_GET_CPU(mess, task_id, time) snprintf( (mess),"task number %dl got the CPU for %d milliseconds",(task_id) ,(time))
#define INFO_MESSAGE_TASK_FINISHED(mess, task_id) snprintf((mess), "task number %dl finished ", (task_id))
