#include "rb_tree.h"
#include "consts.h"
#include "logger.h"

rb_tree* initial_rb_tree() {
	rb_tree* tree = (rb_tree*)malloc(sizeof(rb_tree));
	if (tree == NULL) {
		LOG_ERROR(ERROR_MESSAGE_MEMORY_ALLOCATION_FAILED);
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
	char message[STANDART_SIZE_MESS];
	INFO_MESSAGE_NEW_TASK_INSERT_TO_RB_TREE(message, node->task->id, node->task->execution_time);
	LOG_INFO(message);
}

void rb_tree_insert_task(rb_tree* tree, rb_node* node) {
	if (node == NULL) {
		LOG_ERROR(ERROR_MESSAGE_ACCESSING_NULL_POINTER);
		return;
	}

	if (tree == NULL) {
		LOG_ERROR(ERROR_MESSAGE_TREE_NOT_INITIALIZED);
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
}

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
	if (tree == NULL) {
		LOG_ERROR(ERROR_MESSAGE_TREE_NOT_INITIALIZED);
		return 0;
	}
	return tree->most_left == NULL;
}

//free tree
void free_struct_rb_tree(rb_tree* tree) {
	free_rb_tree(tree->root);
	tree->root = NULL;
	tree->most_left = NULL;
	tree->num_of_tasks = tree->total_weights = 0;
}

void free_rb_tree(rb_node* node) {
	if (node == NULL) {
		LOG_ERROR(ERROR_MESSAGE_ACCESSING_NULL_POINTER);
		return;
	}
	rb_node* temp = node;
	free_rb_tree(node->left);
	free_rb_tree(node->right);
	free_task(temp->task);
	free(temp);
}

//remvoe task from the rb_tree
void remove_node_from_rb_tree(rb_tree* tree, rb_node* node) {
	if (node == NULL) {
		LOG_ERROR(ERROR_MESSAGE_ACCESSING_NULL_POINTER);
		return;
	}

	if (tree == NULL) {
		LOG_ERROR(ERROR_MESSAGE_TREE_NOT_INITIALIZED);
		return;
	}

	if (tree->root == NULL) {
		LOG_ERROR(ERROR_MESSAGE_TREE_EMPTY);
		return;
	}
	rb_node* y = node;
	rb_node* x = NULL;
	int y_original_color = y->color;

	// Finding the node to replace and preparing for deletion
	if (node->left == NULL) {
		x = node->right;
		if (x) x->parent = node->parent;
		if (node->parent == NULL) {
			tree->root = x;
		}
		else if (node == node->parent->left) {
			node->parent->left = x;
		}
		else {
			node->parent->right = x;
		}
		if (node == tree->most_left) {
			tree->most_left = node->right ? node->right : node->parent;
		}
	}
	else if (node->right == NULL) {
		x = node->left;
		if (x) x->parent = node->parent;
		if (node->parent == NULL) {
			tree->root = x;
		}
		else if (node == node->parent->left) {
			node->parent->left = x;
		}
		else {
			node->parent->right = x;
		}
		if (node == tree->most_left) {
			tree->most_left = node->left ? node->left : node->parent;
		}
	}
	else {
		y = node->right;
		while (y->left != NULL) {
			y = y->left;
		}
		y_original_color = y->color;
		x = y->right;
		if (y->parent == node) {
			if (x) x->parent = y;
		}
		else {
			if (x) x->parent = y->parent;
			y->parent->left = x;
			y->right = node->right;
			y->right->parent = y;
		}
		if (node->parent == NULL) {
			tree->root = y;
		}
		else if (node == node->parent->left) {
			node->parent->left = y;
		}
		else {
			node->parent->right = y;
		}
		y->parent = node->parent;
		y->left = node->left;
		y->left->parent = y;
		y->color = node->color;
	}

	if (y_original_color == BLACK && x != NULL) {
		// Rebalancing after deletion
		deleteFixup(tree, x);
	}

	// Updating the number of tasks and the total weight
	tree->num_of_tasks--;
	tree->total_weights -= node->task->weight;

	free(node->task);
	free(node);
}

void deleteFixup(rb_tree* tree, rb_node* x) {
	while (x != tree->root && x->color == BLACK) {
		if (x == x->parent->left) {
			rb_node* w = x->parent->right;
			if (w->color == RED) {
				w->color = BLACK;
				x->parent->color = RED;
				left_rotation(tree, x->parent);
				w = x->parent->right;
			}
			if (w->left->color == BLACK && w->right->color == BLACK) {
				w->color = RED;
				x = x->parent;
			}
			else {
				if (w->right->color == BLACK) {
					w->left->color = BLACK;
					w->color = RED;
					right_rotation(tree, w);
					w = x->parent->right;
				}
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->right->color = BLACK;
				left_rotation(tree, x->parent);
				x = tree->root;
			}
		}
		else {
			rb_node* w = x->parent->left;
			if (w->color == RED) {
				w->color = BLACK;
				x->parent->color = RED;
				right_rotation(tree, x->parent);
				w = x->parent->left;
			}
			if (w->right->color == BLACK && w->left->color == BLACK) {
				w->color = RED;
				x = x->parent;
			}
			else {
				if (w->left->color == BLACK) {
					w->right->color = BLACK;
					w->color = RED;
					left_rotation(tree, w);
					w = x->parent->left;
				}
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->left->color = BLACK;
				right_rotation(tree, x->parent);
				x = tree->root;
			}
		}
	}
	x->color = BLACK;
}

void delete_most_left_leaf(rb_tree* tree) {
	if (tree == NULL) {
		LOG_ERROR(ERROR_MESSAGE_TREE_NOT_INITIALIZED);
		return;
	}

	if (tree->most_left == NULL) {
		LOG_ERROR(ERROR_MESSAGE_ACCESSING_NULL_POINTER);
		return;
	}
	rb_node* most_left_leaf = tree->most_left;

	// Updating the pointer to the new leftmost leaf
	if (most_left_leaf->right != NULL) {
		tree->most_left = most_left_leaf->right;
		while (tree->most_left->left != NULL) {
			tree->most_left = tree->most_left->left;
		}
	}
	else {
		rb_node* parent = most_left_leaf->parent;
		tree->most_left = parent;
		while (tree->most_left != NULL && tree->most_left->left == NULL) {
			tree->most_left = tree->most_left->parent;
		}
	}

	// Deleting the leaf from the tree and maintaining the balance
	remove_node_from_rb_tree(tree, most_left_leaf);
}













