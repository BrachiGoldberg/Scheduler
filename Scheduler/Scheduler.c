#define _CTR_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#include "rb_tree.h"

int main() {

	printf("sizeof rb_tree %d\n", sizeof(rb_tree));
	printf("sizeof rb_node %d\n", sizeof(rb_node));
	printf("sizeof task %d\n", sizeof(task));



	task* task1 = (task*)malloc(sizeof(task));
	task1->vruntime = 0;

	task* task2 = (task*)malloc(sizeof(task));
	task2->vruntime = 1;

	task* task3 = (task*)malloc(sizeof(task));
	task3->vruntime = 2;

	task* task4 = (task*)malloc(sizeof(task));
	task4->vruntime = 3;

	task* task5 = (task*)malloc(sizeof(task));
	task5->vruntime = 4;

	task* task6 = (task*)malloc(sizeof(task));
	task6->vruntime = 5;

	rb_tree* tree = initial_rb_tree();
	rb_tree_task_arrival(tree, task1);
	rb_tree_task_arrival(tree, task2);
	rb_tree_task_arrival(tree, task3);
	rb_tree_task_arrival(tree, task4);
	rb_tree_task_arrival(tree, task5);

	free_struct_rb_tree(tree);
}