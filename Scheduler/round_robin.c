#include "round_robin.h"

void execute_queue(real_time_task_queue* queue) {

	//must be a node in the queue
	queue_node* node = pop_task_node(queue);
	real_time_task* current_task = node->task;

	//calculate the current quantum
	double quantum = SCHED_LATENCY * (current_task->weight / queue->total_weights);

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
	current_task->remaining_time -= sleep_time;
	current_task->execution_time += sleep_time;

	//check why the loop finished
	if (current_task->remaining_time <= 0) {
		queue->total_weights -= current_task->weight;

		free_queue_node(node);
	}
	else {
		push_task_node(queue, node);
	}
}