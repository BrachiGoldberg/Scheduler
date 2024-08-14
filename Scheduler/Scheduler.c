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
		rb_tree_task_arrival(sched_point->tasks_tree, new_task);
	}
}
