#include "real_time_task_queue.h"

void push_task_node(real_time_task_queue* real_time_task_queue, queue_node* real_time_node) {
	// Check if the queue or node is NULL and log an error
	if (real_time_task_queue == NULL) {
		LOG_ERROR(ERROR_MESSAGE_QUEUE_NOT_INITIALIZED);
		return;
	}

	if (real_time_node == NULL) {
		LOG_ERROR(ERROR_MESSAGE_ACCESSING_NULL_POINTER);
		return;
	}

	//lock the queue
	lock_queue_mutex();

	// Insert the new node at the end of the queue
	if (real_time_task_queue->rear) {
		real_time_task_queue->rear->next = real_time_node;
	}
	else {
		real_time_task_queue->front = real_time_node;
	}
	real_time_task_queue->rear = real_time_node;


	real_time_task_queue->num_of_tasks++;
	real_time_task_queue->total_weights += real_time_node->task->weight;
	
	//release the queue
	release_queue_mutex();

	// Log an info message about the new task insertion
	char message[STANDART_SIZE_MESS];
	INFO_MESSAGE_NEW_TASK_INSERT_TO_QUEUE(message, real_time_node->task->id, real_time_node->task->remaining_time);
	LOG_INFO(message);
}

queue_node* pop_task_node(real_time_task_queue* real_time_task_queue) {
	if (real_time_task_queue == NULL) {
		LOG_ERROR(ERROR_MESSAGE_QUEUE_NOT_INITIALIZED);
		return NULL;
	}

	if (real_time_task_queue->front == NULL) {
		LOG_ERROR(ERROR_MESSAGE_QUEUE_EMPTY);
		return NULL;
	}

	//lock the queue
	lock_queue_mutex();

	queue_node* queue_node = real_time_task_queue->front;
	real_time_task_queue->front = real_time_task_queue->front->next;
	if (!real_time_task_queue->front) {
		real_time_task_queue->rear = NULL;
	}

	queue_node->next = NULL;

	//release the queue
	release_queue_mutex();

	real_time_task_queue->num_of_tasks--;
	real_time_task_queue->total_weights -= queue_node->task->weight;

	// Log an info message about the task removal
	char message[STANDART_SIZE_MESS];
	INFO_MESSAGE_TASK_REMOVED_FROM_QUEUE(message, queue_node->task->id);
	LOG_INFO(message);

	return queue_node;
}

int is_queue_empty(real_time_task_queue* real_time_task_queue) {
	if (real_time_task_queue == NULL) {
		LOG_ERROR(ERROR_MESSAGE_ACCESSING_NULL_POINTER);
		return 1; // Consider the queue empty if it’s not initialized
	}
	return real_time_task_queue->front == NULL;
}

real_time_task_queue* initialize_queue() {
	// Allocate memory for the queue
	real_time_task_queue* queue = (real_time_task_queue*)malloc(sizeof(real_time_task_queue));
	if (queue == NULL) {
		LOG_ERROR(ERROR_MESSAGE_MEMORY_ALLOCATION_FAILED);
		return NULL;
	}

	queue->front = NULL;
	queue->rear = NULL;
	queue->total_weights = 0.0;
	queue->num_of_tasks = 0;

	return queue;
}


void free_queue(real_time_task_queue* queue) {
	if (queue == NULL) return;

	queue_node* current = queue->front;
	queue_node* next;

	// Free all nodes in the queue
	while (current != NULL) {
		next = current->next;
		free(current);
		current = next;
	}

	// Reset queue attributes
	queue->front = NULL;
	queue->rear = NULL;
	queue->total_weights = 0.0;
	queue->num_of_tasks = 0;
}
