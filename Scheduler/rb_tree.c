#include "rb_tree.h"
#include "consts.h"
#include "logger.h"

rb_tree* initial_rb_tree() {
	rb_tree* tree = (rb_tree*)malloc(sizeof(rb_tree));
	if (tree == NULL) {
		char message[STANDART_SIZE_MESS];
		ERROR_MESSAGE_MEMORY_ALLOCATION_FAILED(message);
		LOG_ERROR(message);
		exit(EXIT_FAILURE); // Use a standard exit code
	}

	tree->root = tree->most_left = NULL;
	tree->num_of_tasks = 0;
	tree->total_weights = 0;

	char message[STANDART_SIZE_MESS];
	snprintf(message, sizeof(message), "Initialized a new red-black tree");
	LOG_INFO(message);

	return tree;
}

void rb_tree_new_task_arrival(rb_tree* tree, task* task) {
	// Create new node
	rb_node* node = create_rb_node(task);

	// Update the tree properties
	tree->num_of_tasks++;
	tree->total_weights += task->weight;

	rb_tree_insert_task(tree, node);

	// Info log message
	char mess[STANDART_SIZE_MESS];
	INFO_MESSAGE_NEW_TASK_INSERT_TO_RB_TREE(mess, node->task->id, node->task->execution_time);
	LOG_INFO(mess);
}

void rb_tree_insert_task(rb_tree* tree, rb_node* node) {
	if (node == NULL) {
		char message[STANDART_SIZE_MESS];
		ERROR_MESSAGE_ACCESSING_NULL_POINTER(message);
		LOG_ERROR(message);
		return;
	}

	if (tree == NULL) {
		char message[STANDART_SIZE_MESS];
		ERROR_MESSAGE_TREE_NOT_INITIALIZED(message);
		LOG_ERROR(message);
		return;
	}

	node->color = RED;

	//lock the tree
	lock_tree_mutex();

	if (tree->root == NULL) {
		node->task->vruntime = 0;
		node->color = BLACK;
		tree->root = tree->most_left = node;
	}
	else {
		node->task->vruntime = tree->most_left->task->weight + 0.5;
		add_node_to_tree(tree->root, node);

		if (node->parent->color == RED) {
			if (node->parent->left == node) {
				if (node->parent->right != NULL && node->parent->right->color == RED) {
					change_colors_hierarchical(tree, node);
				}
				else {
					rotate_tree(tree, node);
				}
			}
			else {
				if (node->parent->left != NULL && node->parent->left->color == RED) {
					change_colors_hierarchical(tree, node);
				}
				else {
					rotate_tree(tree, node);
				}
			}
		}
	}

	//release the tree
	release_tree_mutex();
}

void add_node_to_tree(rb_node* root, rb_node* node) {
	if (root == NULL)
		return;

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
	if (current->parent == NULL) {
		char message[STANDART_SIZE_MESS];
		snprintf(message, sizeof(message), "Rotation skipped as parent of node is NULL");
		LOG_DEBUG(message);
		return;
	}

	rb_node* node_parent = current->parent;
	rb_node* grandfather = node_parent->parent;
	if (grandfather == NULL) {
		char message[STANDART_SIZE_MESS];
		snprintf(message, sizeof(message), "Rotation skipped as the grandparent of the node is NULL");
		LOG_DEBUG(message);
		return;
	}

	if (grandfather->left == node_parent) {
		if (grandfather->right == NULL) {
			if (node_parent->left == current) {
				right_rotation(tree, current->parent);
				change_colors_after_rotation(current->parent);
			}
			else {
				left_right_rotation(tree, current);
			}
		}
		else if (grandfather->right->color == RED) {
			change_colors_hierarchical(tree, grandfather);
		}
		else {
			if (node_parent->left == current) {
				right_rotation(tree, current->parent);
				change_colors_after_rotation(current->parent);
			}
			else {
				left_right_rotation(tree, current);
			}
		}
	}
	else {
		if (grandfather->left == NULL) {
			if (node_parent->right == current) {
				left_rotation(tree, current->parent);
				change_colors_after_rotation(current->parent);
			}
			else {
				right_left_rotation(tree, current);
			}
		}
		else if (grandfather->left->color == RED) {
			change_colors_hierarchical(tree, grandfather);
		}
		else {
			if (node_parent->left == current) {
				right_left_rotation(tree, current);
			}
			else {
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

	char message[STANDART_SIZE_MESS];
	snprintf(message, sizeof(message), "Changed colors hierarchically for node %p", (void*)grandfather);
	LOG_DEBUG(message);
}

void left_right_rotation(rb_tree* tree, rb_node* node) {
	left_rotation(tree, node);
	right_rotation(tree, node);
	change_colors_after_rotation(node);

	char message[STANDART_SIZE_MESS];
	snprintf(message, sizeof(message), "Performed left-right rotation for node %p", (void*)node);
	LOG_DEBUG(message);
}

void right_left_rotation(rb_tree* tree, rb_node* node) {
	right_rotation(tree, node);
	left_rotation(tree, node);
	change_colors_after_rotation(node);

	char message[STANDART_SIZE_MESS];
	snprintf(message, sizeof(message), "Performed right-left rotation for node %p", (void*)node);
	LOG_DEBUG(message);
}

void left_rotation(rb_tree* tree, rb_node* node) {
	rb_node* left = node->left;
	if (left != NULL)
		left->parent = node->parent;
	node->parent->right = left;

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

	char message[STANDART_SIZE_MESS];
	snprintf(message, sizeof(message), "Performed left rotation for node %p", (void*)node);
	LOG_DEBUG(message);
}

void right_rotation(rb_tree* tree, rb_node* node) {
	rb_node* right = node->right;
	if (right != NULL)
		right->parent = node->parent;
	node->parent->left = right;

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

	char message[STANDART_SIZE_MESS];
	snprintf(message, sizeof(message), "Performed right rotation for node %p", (void*)node);
	LOG_DEBUG(message);
}

void change_colors_after_rotation(rb_node* node) {
	node->color = BLACK;
	if (node->left)
		node->left->color = RED;
	if (node->right)
		node->right->color = RED;
}
int is_most_left_empty(rb_tree* tree) {
	if (tree == NULL) {
		char message[STANDART_SIZE_MESS];
		ERROR_MESSAGE_TREE_NOT_INITIALIZED(message);
		LOG_ERROR(message);

		return 0;
	}
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
















