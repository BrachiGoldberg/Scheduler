#include "round_robin.h"

void execute_queue(struct real_time_task_queue* queue) {

	//must be a node in the queue
	struct queue_node* node = pop_task_node(queue);
	struct real_time_task* current_task = node->task;

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
	/*int success = */ Sleep(sleep_time);
	/*if (success > 0) {

		//the task get only success time.
		sleep_time = success;
	}*/
	//update the task's times
	current_task->remaining_time -= sleep_time;
	current_task->execution_time += sleep_time;

	//check why the loop finished
	if (current_task->remaining_time <= 0) {
		//remove the task's weight from the toal weights
		queue->total_weights -= current_task->weight;
		//tha task finished - remove the task from the system
		free_queue_node(node);
	}
	else {
		//insert the task again to the end of the queue
		push_task_node(queue, node);
	}
}