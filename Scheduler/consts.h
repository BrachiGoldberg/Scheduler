



#define STANDART_SIZE_MESS 256

#define INFO_MESSAGE_TASK_GET_CPU(mess, task_id, time) snprintf( (mess),"task number %dl got the CPU for %d milliseconds",(task_id) ,(time))
#define INFO_MESSAGE_TASK_FINISHED(mess, task_id) snprintf((mess), "task number %dl finished ", (task_id))
