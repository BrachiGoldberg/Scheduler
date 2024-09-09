#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include "scheduler.h"
#include "rb_tree.h"
#include "real_time_task_queue.h"
#include "mutex.h"
#include "logger.h"
#include "general_settings.h"
#include "consts_logs.h"


//int main() {
//	scheduler sched;
//
//	//Initialize the scheduler and other necessary components
//	initial_all_structs(&sched);
//
//	HANDLE input_thread_handle, task_thread_handle;
//
//	//Create the input thread
//	create_input_thread(&input_thread_handle, &sched);
//
//	// Create the task execution thread
//	create_task_thread(&task_thread_handle, &sched);
//
//	// Wait for threads to finish (they run indefinitely in this case)
//	WaitForSingleObject(input_thread_handle, INFINITE);
//	WaitForSingleObject(task_thread_handle, INFINITE);
//
//	// Clean up resources
//	CloseHandle(input_thread_handle);
//	CloseHandle(task_thread_handle);
//
//	CloseHandle(queue_mutex);
//	CloseHandle(tree_mutex);
//
//	free_queue(sched.queue);
//	free_struct_rb_tree(sched.tasks_tree);
//
//	return 0;
//}

