#include "scheduler.h"

void new_task_arrival(int nice, double execution_time, scheduler* sched_point) {
	long double weight = DEFULT_WEIGHT / pow(1.25, nice);

	// Create a log message for the new task arrival
	char message[STANDART_SIZE_MESS];
	if (nice < -20) {
		queue_node* node = create_queue_node(nice, execution_time, weight);
		push_task_node(sched_point->queue, node);

		// Log the addition of a new task to the queue
		INFO_MESSAGE_NEW_TASK_INSERT_TO_QUEUE(message, node->task->id, execution_time);
		LOG_INFO(message);
	}
	else {
		task* new_task = create_task(nice, execution_time, weight);
		rb_tree_new_task_arrival(sched_point->tasks_tree, new_task);

	}
}

void scheduling_tasks(scheduler* sched) {
	if (sched == NULL) {
		LOG_ERROR(ERROR_MESSAGE_ACCESSING_NULL_POINTER);
	}

	// Log the start of the scheduling process
	LOG_INFO(INFO_MESSAGE_START_SECHEDULING_TASKS);
	int time_queue, time_tree;
	char message[STANDART_SIZE_MESS];
	
	//scheduling tasks
	while (1) {

		//first, schedule the tasks' queue for QUANTUM_QUEUE times
		//while the queue is not empty
		for (time_queue = 0; !is_queue_empty(sched->queue) && time_queue < QUANTUM_QUEUE;
			time_queue++) {
			execute_queue(sched->queue);
		}

		/*INFO_MESSAGE_QUEUE_GOT_CPU(message, time_queue);
		LOG_INFO(message);*/

		//if the QUANTUM_QUEUE time finished or the queue is empty,
		//the scheduler schedule the tasks' rb_tree
		for (time_tree = 0; !is_most_left_empty(sched->tasks_tree) && time_tree < QUANTUM_TREE;
			time_tree++) {
			execute_tree(sched->tasks_tree);
		}

		//INFO_MESSAGE_TREE_GOT_CPU(message, time_tree);
		//LOG_INFO(message);
	}

}

DWORD WINAPI input_thread(LPVOID param) {
	scheduler* sched = (scheduler*)param;
	int nice;
	double execution_time;
	srand(time(NULL));
	while(1) {
		scanf("%d", &nice);
		scanf("%lf", &execution_time);
		execution_time *= 1000;
		new_task_arrival(nice, execution_time, sched);
	}

	return 0;
}

DWORD WINAPI task_thread(LPVOID param) {
	scheduler* sched = (scheduler*)param;

	// Call the function that the thread is supposed to operate
	scheduling_tasks(sched);

	return 0;
}