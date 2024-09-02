#include "scheduler.h"
#include "general_settings.h"
#include "logger.h"
#include "consts.h"

void new_task_arrival(int nice, double execution_time, scheduler* sched_point) {
    long double weight = DEFULT_WEIGHT / pow(1.25, nice);

    // Create a log message for the new task arrival
    char message[STANDART_SIZE_MESS];
    if (nice < -20) {
        struct queue_node* node = create_queue_node(nice, execution_time, weight);
        push_task_node(sched_point->queue, node);

        // Log the addition of a new task to the queue
        INFO_MESSAGE_NEW_TASK_INSERT_TO_QUEUE(message, node->task->id, execution_time);
        LOG_INFO(message);
    }
    else {
        task* new_task = create_task(nice, execution_time, weight);
        rb_tree_new_task_arrival(sched_point->tasks_tree, new_task);

        // Log the addition of a new task to the red-black tree
        INFO_MESSAGE_NEW_TASK_INSERT_TO_RB_TREE(message, new_task->id, execution_time);
        LOG_INFO(message);
    }
}

void scheduling_tasks(scheduler* sched) {
    // Log the start of the scheduling process
    LOG_INFO("Starting task scheduling process");
    char message[STANDART_SIZE_MESS];

    // Scheduling tasks
    while (1) {
        // First, schedule the tasks' queue for QUANTUM_QUEUE times
        // while the queue is not empty
        for (int time_queue = 0; !is_queue_empty(sched->queue) && time_queue < QUANTUM_QUEUE; time_queue++) {
            // Log the start of queue execution
            //char message[STANDART_SIZE_MESS];
           

            execute_queue(sched->queue);
        }

        // If the QUANTUM_QUEUE time finished or the queue is empty,
        // the scheduler schedules the tasks' rb_tree
        for (int time_tree = 0; !is_most_left_empty(sched->tasks_tree) && time_tree < QUANTUM_TREE; time_tree++) {
            // Log the start of tree execution
            

            execute_tree(sched->tasks_tree);
        }
    }
}
