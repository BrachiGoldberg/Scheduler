#include "scheduler.h"

void scheduling_tasks(scheduler* sched) {

	//scheduling tasks
	while (1) {

		//first, schedule the tasks' queue for QUANTUM_QUEUE times
		//while the queue is not empty
		for (int time_queue = 0; is_queue_empty(sched->queue) && time_queue < QUANTUM_QUEUE;
			time_queue++) {
			execute_queue(sched->queue);
		}

		//if the QUANTUM_QUEUE time finished or the queue is empty,
		//the scheduler schedule the tasks' rb_tree
		for (int time_tree = 0; is_most_left_empty(sched->tasks_tree) && time_tree < QUANTUM_TREE;
			time_tree++) {
			execute_tree(sched->tasks_tree);
		}
	}

}