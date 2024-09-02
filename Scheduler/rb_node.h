#ifndef _RB_NODE_H
#define _RB_NODE_H

#include "task.h"
#include "logger.h"
#include "consts.h"

#define BLACK 0
#define RED 1

typedef struct rb_node {
	task* task;
	char color;
	struct rb_node* left;
	struct rb_node* right;
	struct rb_node* parent;
}rb_node;

rb_node* create_rb_node(task* task);

void free_rb_node(rb_node* node);

#endif // !1

