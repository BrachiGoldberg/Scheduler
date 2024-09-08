#include "round_robin.h"

void execute_queue(real_time_task_queue* queue) {
	//LOG_TRACE(TRACE_MESSAGE_EXECUTE_REAL_TIME_TASK);

	//must be a node in the queue
	queue_node* node = pop_task_node(queue);
	real_time_task* current_task = node->task;

	//calculate the current quantum
	double quantum = SCHED_LATENCY * (current_task->weight / (queue->total_weights + current_task->weight));

	char message[STANDART_SIZE_MESS];
	DEBAG_MESSAGE_CALCULATE_QUANTUM(message, current_task->id, quantum);
	LOG_DEBUG(message);

	double sleep_time;//in milliseconds
	//choose to sleep_time (the task's execution_time):
	if (quantum > MIN_QUANTUM) {
		if (current_task->remaining_time > quantum)
			sleep_time = quantum;
		else
			sleep_time = current_task->remaining_time;
	}
	else {
		if (MIN_QUANTUM > current_task->remaining_time)
			sleep_time = current_task->remaining_time;
		else
			sleep_time = MIN_QUANTUM;
	}
	current_task->quantum = sleep_time;

	//sleep the system for sleep_time milliseconds
	Sleep((DWORD)sleep_time);

	DEBUG_MESSAGE_TASK_SCHEDULED(message, current_task->id, sleep_time);
	LOG_DEBUG(message);

	//update the task's times
	current_task->remaining_time -= sleep_time;
	current_task->execution_time += sleep_time;

	////info log massege
	//char mess[STANDART_SIZE_MESS];
	//INFO_MESSAGE_TASK_GET_CPU(mess, current_task->id, sleep_time);
	//LOG_INFO(mess);

	//check why the loop finished
	if (current_task->remaining_time <= 0) {
		
		//remove the task's weight from the toal weights
		lock_queue_mutex();
		queue->total_weights -= current_task->weight;
		release_queue_mutex();

		char mess[STANDART_SIZE_MESS];
		INFO_MESSAGE_TASK_FINISHED(mess, current_task->id);
		LOG_INFO(mess);

		//the task finished - remove the task from the system
		free_queue_node(node);
	}
	else {
		//insert the task again to the end of the queue
		push_task_node(queue, node);
	}
}
