#include "scheduler.h"

ID = 0;

long get_id() {
	return ++ID;
}

void new_task_arrival(int nice, double execution_time, scheduler* sched_point) {
	long double weight = DEFUALT_WEIGHT / pow(1.25, nice);

	// Create a log message for the new task arrival
	char message[STANDART_SIZE_MESS];
	if (nice < -20) {
		queue_node* node = create_queue_node(nice, execution_time, weight);
		queue_new_task_arrival(sched_point->queue, node);
	}
	else {
		task* new_task = create_task(nice, execution_time, weight);
		rb_tree_new_task_arrival(sched_point->tasks_tree, new_task);
	}
	SetEvent(event_handler);
	LOG_DEBUG(DEBUG_MESSAGE_WAKE_UP_TASK_THREAD);
}

void scheduling_tasks(scheduler* sched) {
	if (sched == NULL) {
		LOG_ERROR(ERROR_MESSAGE_ACCESSING_NULL_POINTER);
	}
	// Log the start of the scheduling process
	LOG_INFO(INFO_MESSAGE_START_SECHEDULING_TASKS);
	int number_of_tasks_per_queue, number_of_tasks_per_tree;
	char message[STANDART_SIZE_MESS];

	//scheduling tasks
	while (1) {

		//if there is no task available the thread go to sleep
		if (is_queue_empty(sched->queue) && is_most_left_empty(sched->tasks_tree)) {
			LOG_DEBUG(DEBUG_MESSAGE_NO_TASK_AVAILABLE);	
			WaitForSingleObject(event_handler, INFINITE);
			ResetEvent(event_handler);
		}

		//first, schedule the tasks' queue for QUANTUM_QUEUE times
		//while the queue is not empty
		for (number_of_tasks_per_queue = 0; !is_queue_empty(sched->queue) && number_of_tasks_per_queue < QUANTUM_QUEUE;
			number_of_tasks_per_queue++) {
			execute_queue(sched->queue);
		}

		INFO_MESSAGE_QUEUE_GOT_CPU(message, number_of_tasks_per_queue);
		LOG_INFO(message);

		//if the QUANTUM_QUEUE time finished or the queue is empty,
		//the scheduler schedule the tasks' rb_tree
		for (number_of_tasks_per_tree = 0; !is_most_left_empty(sched->tasks_tree) && number_of_tasks_per_tree < QUANTUM_TREE;
			number_of_tasks_per_tree++) {
			execute_tree(sched->tasks_tree);
		}

		INFO_MESSAGE_TREE_GOT_CPU(message, number_of_tasks_per_tree);
		LOG_INFO(message);
	}
}

DWORD WINAPI input_thread(LPVOID param) {
	scheduler* sched = (scheduler*)param;
	int nice;
	double execution_time;
	while (1) {
		scanf("%d", &nice);
		scanf("%lf", &execution_time);
		new_task_arrival(nice, execution_time, sched);
	}

	return 0;
}

DWORD WINAPI task_thread(LPVOID param) {
	scheduler* sched = (scheduler*)param;

	// Call the function that the thread is supposed to operate
	scheduling_tasks(sched);

	return 0;
}

void initial_all_structs(scheduler* sched) {
	int success = logger_initFileLogger(LOGGER_FILE, MAX_LOGGER_FILE_SIZE, MAX_LOGGER_BUCKUP_FILES);
	if (success == 0) {
		printf(ERROR_MESSAGE_LOGGER_INIT_FAILED);
		exit(EXIT_FAILURE);
	}
	logger_setLevel(LogLevel_TRACE);

	sched->tasks_tree = initial_rb_tree();
	sched->queue = initialize_queue();

	create_tree_mutex();
	create_queue_mutex();

	event_handler = CreateEvent(NULL, TRUE, FALSE, NULL);
}

void create_input_thread(HANDLE* thread_name, scheduler* sched) {
	*thread_name = CreateThread(NULL, 0, input_thread, sched, 0, NULL);

	if (thread_name == NULL) {
		LOG_ERROR(ERROR_MESSAGE_CREATE_INPUT_TREAD_FAILED);
		return EXIT_FAILURE;
	}
}

void create_task_thread(HANDLE* thread_name, scheduler* sched) {
	*thread_name = CreateThread(NULL, 0, task_thread, sched, 0, NULL);

	if (thread_name == NULL) {
		LOG_ERROR(ERROR_MESSAGE_CREATE_TASK_TREAD_FAILED);
		return EXIT_FAILURE;
	}
}
