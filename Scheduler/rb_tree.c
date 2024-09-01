#include "rb_tree.h"
#include "consts.h"
#include "logger.h"

rb_tree* initial_rb_tree() {

	rb_tree* tree = (rb_tree*)malloc(sizeof(rb_tree));
	tree->root = tree->most_left = NULL;
	tree->num_of_tasks = 0;
	tree->total_weights = 0;

	return tree;
}

void rb_tree_new_task_arrival(rb_tree* tree, task* task){
	//create new node
	rb_node* node = create_rb_node(task);

	//update the tree properties
	tree->num_of_tasks++;
	tree->total_weights += task->weight;

	rb_tree_task_arrival(tree, node);

	//info log message
	char mess[STANDART_SIZE_MESS];
	INFO_MESSAGE_NEW_TASK_INSERT_TO_RB_TREE(mess, node->task->id, node->task->execution_time);
	LOG_INFO(mess);
}

//insert task to the rb_tree
void rb_tree_insert_task(rb_tree* tree, rb_node* node) {
	
	if (node == NULL) {
		//ERROR
	}

	if (tree == NULL) {
		//ERROR
	}

	node->color = RED;

	//TODO lock the tree

	//if the tree is empty, 
	if (tree->root == NULL) {
		node->task->vruntime = 0;
		node->color = BLACK;
		tree->root = tree->most_left = node;
	}
	else {
		//the tree is not empty
		
		//update the vruntime by the most left leaf
		node->task->vruntime = tree->most_left->task->weight + 0.5;

		//insert the node to the tree
		add_node_to_tree(tree->root, node);

		//check the colors
		if (node->parent->color == RED) {

			//check uncle's color
			if (node->parent->left == node) {
				//node is a left child
				if (node->parent->right != NULL && node->parent->right->color == RED) {
					change_colors_hierarchical(tree, node);
				}
				else {
					//rotate the tree
					rotate_tree(tree, node);
				}
			}
			else {
				//node is a right child
				if (node->parent->left != NULL && node->parent->left->color == RED) {
					change_colors_hierarchical(tree, node);
				}
				else {
					//rotate the tree
					rotate_tree(tree, node);
				}
			}
		}

	}
}

void add_node_to_tree(rb_node* root, rb_node* node) {

	if (root == NULL)
		return;

	//if the node smaller
	if (root->task->vruntime > node->task->vruntime) {

		if (root->left != NULL) {
			add_node_to_tree(root->left, node);
		}
		else {
			root->left = node;
			node->parent = root;
		}
	}
	else {
		//the node is bigger;
		if (root->right != NULL) {
			add_node_to_tree(root->right, node);
		}
		else {
			root->right = node;
			node->parent = root;
		}
	}


}

void rotate_tree(rb_tree* tree, rb_node* current) {

	//TODO adding validators of not null nodes

	rb_node* node_parent = current->parent;
	rb_node* grandfather = node_parent->parent;
	if (grandfather == NULL) {
		//node_parent is a root
		//it is forced the node_parent color is black - so this condition never be true
		return;//??
	}

	//if node_parent is a left child
	else if (grandfather->left == node_parent) {

		//if there is no uncle
		if (grandfather->right == NULL) {

			if (node_parent->left == current) {
				//node is a left child
				right_rotation(tree, current->parent);
				change_colors_after_rotation(current->parent);
			}
			else {
				//node is a right child
				left_right_rotation(tree, current);
			}
		}
		else if (grandfather->right->color == RED) {
			//uncle's node is a red node
			change_colors_hierarchical(tree, grandfather);
		}
		else {
			//need to rotate the tree.

			//if node is a left child
			if (node_parent->left == current) {
				//left left rotation (LL)
				right_rotation(tree, current->parent);
				change_colors_after_rotation(current->parent);
			}
			else {
				//left right rotation (LR)
				left_right_rotation(tree, current);
			}
		}
	}
	else {
		//node_parent is a right child

		//if there is no uncle
		if (grandfather->left == NULL) {
			if (node_parent->right == current) {
				//node is a right child
				left_rotation(tree, current->parent);
				change_colors_after_rotation(current->parent);
			}
			else {
				//node is a left child
				right_left_rotation(tree, current);
			}
		}
		//checks the uncle's color
		else if (grandfather->left->color == RED) {
			//uncle's node is a red node
			change_colors_hierarchical(tree, grandfather);
		}
		else {
			//need to rotate
			//if node is a left child
			if (node_parent->left == current) {
				//right left rotation (RL)
				right_left_rotation(tree, current);
			}
			else {
				//left rotation (RR)
				left_rotation(tree, current->parent);
				change_colors_after_rotation(current->parent);
			}
		}
	}


}

void change_colors_hierarchical(rb_tree* tree, rb_node* grandfather) {

	grandfather->left->color = grandfather->right->color = BLACK;

	if (grandfather->parent != NULL && grandfather->parent->color == RED) {
		rotate_tree(tree, grandfather);
	}
}

//rotation
// left right rotation
void left_right_rotation(rb_tree* tree, rb_node* node) {

	left_rotation(tree, node);
	right_rotation(tree, node);
	change_colors_after_rotation(node);
}

void right_left_rotation(rb_tree* tree, rb_node* node) {

	right_rotation(tree, node);
	left_rotation(tree, node);
	change_colors_after_rotation(node);
}

void left_rotation(rb_tree* tree, rb_node* node) {

	rb_node* left = node->left;
	if (left != NULL)
		left->parent = node->parent;
	node->parent->right = left;

	//checking if the node's parent is not the root
	if (node->parent != tree->root) {
		if (node->parent->parent->left == node->parent) {
			node->parent->parent->left = node;
		}
		else {
			node->parent->parent->right = node;
		}
	}
	else {
		tree->root = node;
	}

	node->left = node->parent;
	node->parent = node->parent->parent;
	node->left->parent = node;
}

void right_rotation(rb_tree* tree, rb_node* node) {

	rb_node* right = node->right;
	if (right != NULL)
		right->parent = node->parent;
	node->parent->left = right;

	//checking if the node's parent is not the root
	if (node->parent != tree->root) {
		if (node->parent->parent->left == node->parent) {
			node->parent->parent->left = node;
		}
		else {
			node->parent->parent->right = node;
		}
	}
	else {
		tree->root = node;
	}

	node->right = node->parent;
	node->parent = node->parent->parent;
	node->right->parent = node;
}

void change_colors_after_rotation(rb_node* node) {
	node->color = BLACK;
	if (node->left)
		node->left->color = RED;
	if (node->right)
		node->right->color = RED;
}

int is_most_left_empty(rb_tree* tree) {
	return tree->most_left == NULL;
}
//remvoe task from the rb_tree

//free tree
void free_struct_rb_tree(rb_tree* tree) {

	free_rb_tree(tree->root);
	tree->root = NULL;
	tree->most_left = NULL;
	tree->num_of_tasks = tree->total_weights = 0;
}

void free_rb_tree(rb_node* node) {

	if (node == NULL)
		return;

	rb_node* temp = node;
	free_rb_tree(node->left);
	free_rb_tree(node->right);
	free_task(temp->task);
	free(temp);
}

void remove_node_from_rb_tree(rb_tree* tree, rb_node* node) {
	if (node == NULL || tree == NULL)
		return;

	tree->num_of_tasks--;
	tree->total_weights -= node->task->weight;
	free_rb_node(node);
}