#include "scheduler.h"
#include "general_settings.h"

void new_task_arrival(int nice, double execution_time, scheduler* sched_point) {
	long double weight = DEFULT_WEIGHT / pow(1.25, nice);
	if (nice < -20) {
		struct queue_node* node = create_queue_node(nice, execution_time, weight);
		push_task_node(sched_point->queue, node);
	}
	else {
		task* new_task = create_task(nice, execution_time, weight);
		rb_tree_new_task_arrival(sched_point->tasks_tree, new_task);
	}
}

void scheduling_tasks(scheduler* sched) {

	//scheduling tasks
	while (1) {

		//first, schedule the tasks' queue for QUANTUM_QUEUE times
		//while the queue is not empty
		for (int time_queue = 0; !is_queue_empty(sched->queue) && time_queue < QUANTUM_QUEUE;
			time_queue++) {
			execute_queue(sched->queue);
		}

		//if the QUANTUM_QUEUE time finished or the queue is empty,
		//the scheduler schedule the tasks' rb_tree
		for (int time_tree = 0; !is_most_left_empty(sched->tasks_tree) && time_tree < QUANTUM_TREE;
			time_tree++) {
			execute_tree(sched->tasks_tree);
		}
	}

}