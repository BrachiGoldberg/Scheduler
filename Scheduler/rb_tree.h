#ifndef RB_TREE_H
#define RB_TREE_H

#include <stdlib.h>

#include "rb_node.h"
#include "mutex.h"
#include "consts_logs.h"
#include "logger.h"

typedef struct {
	int num_of_tasks;
	rb_node* root;
	rb_node* most_left;
	long double total_weights;
}rb_tree;


rb_tree* initial_rb_tree();

void rb_tree_new_task_arrival(rb_tree* tree, task* task);
void rb_tree_insert_task(rb_tree* tree, rb_node* node);
void add_node_to_tree(rb_node* root, rb_node* node);
void rotate_tree(rb_tree* tree, rb_node* node);
void change_colors_hierarchical(rb_tree* tree, rb_node* grandfather);

//rotation

void left_right_rotation(rb_tree* tree, rb_node* node);
void right_left_rotation(rb_tree* tree, rb_node* node);
void left_rotation(rb_tree* tree, rb_node* node);
void right_rotation(rb_tree* tree, rb_node* node);

void change_colors_after_rotation(rb_node* node);

//check if the most left NULL
int is_most_left_empty(rb_tree* tree);

//free tree
void free_struct_rb_tree(rb_tree* tree);
void free_rb_tree(rb_node* node);

void remove_node_from_rb_tree(rb_tree* tree, rb_node* node);
void deleteFixup(rb_tree* tree, rb_node* x);
void delete_most_left_leaf(rb_tree* tree);

#endif // !RB_TREE_H