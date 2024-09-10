#include "round_robin.h"

void execute_queue(real_time_task_queue* queue) {
	//LOG_TRACE(TRACE_MESSAGE_EXECUTE_REAL_TIME_TASK);

	//must be a node in the queue
	queue_node* node = pop_task_node(queue);
	real_time_task* current_task = node->task;

	//calculate the current quantum
	double quantum = SCHED_LATENCY * (current_task->weight / queue->total_weights);
	if (quantum < 0) {
		LOG_ERROR("something wrang");
	}

	char message[STANDART_SIZE_MESS];
	DEBAG_MESSAGE_CALCULATE_QUANTUM(message, current_task->id, quantum);
	LOG_DEBUG(message);

	//sleep time in milliseconds
	double sleep_time = min(max(quantum, MIN_QUANTUM), current_task->remaining_time);

	//sleep the system for sleep_time milliseconds
	Sleep((DWORD)sleep_time);

	//update the task's times
	current_task->remaining_time -= sleep_time;
	current_task->execution_time += sleep_time;

	////info log massege
	INFO_MESSAGE_TASK_GET_CPU(message, current_task->id, sleep_time);
	LOG_INFO(message);

	//check why the loop finished
	if (current_task->remaining_time <= 0) {
		
		//remove the task's weight from the toal weights
		lock_queue_mutex();
		queue->num_of_tasks--;
		queue->total_weights -= current_task->weight;
		release_queue_mutex();

		char mess[STANDART_SIZE_MESS];
		INFO_MESSAGE_TASK_FINISHED(mess, current_task->id);
		LOG_INFO(mess);

		//the task finished - remove the task from the system
		free_queue_node(node);

		logger_flush();
	}
	else {
		//insert the task again to the end of the queue
		push_task_node(queue, node);
	}
}
