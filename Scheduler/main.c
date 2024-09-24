#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include "scheduler.h"
#include "rb_tree.h"
#include "real_time_task_queue.h"
#include "mutex.h"
#include "logger.h"
#include "general_settings.h"
#include "consts_logs.h"

// Global variables
HANDLE input_thread_handle, task_thread_handle;
scheduler sched;

// Function to clean up resources
void cleanup_resources() {
    LOG_INFO(INFO_MESSAGE_CLEANING_UP_RESOURCES);
    CloseHandle(input_thread_handle);
    CloseHandle(task_thread_handle);

    CloseHandle(queue_mutex);
    CloseHandle(tree_mutex);

    free_queue(sched.queue);
    free_struct_rb_tree(sched.tasks_tree);
}

// Signal handler for SIGINT (e.g., Ctrl+C)
void cleanup(int signum) {
    LOG_INFO(INFO_MESSAGE_CLOSE_THE_WINDOW_CTRL_C(signum));
    cleanup_resources();
    exit(1);
}

// Handler for console close event (e.g., clicking the 'X' button)
BOOL WINAPI ConsoleHandler(DWORD signal) {
    if (signal == CTRL_CLOSE_EVENT) {
        LOG_INFO(INFO_MESSSAGE_CLOSE_THE_WINDOW_X_BUTTON);
        cleanup_resources();
        return TRUE;
    }
    return FALSE;
}

int main() {
    // Initialize the scheduler and other necessary components
    initial_all_structs(&sched);

    // Register ConsoleHandler for console window close event
    if (SetConsoleCtrlHandler(ConsoleHandler, TRUE)) {
        LOG_INFO(INFO_MESSAGE_SET_CONSOLE_HANDLER);
    }
    else {
        LOG_ERROR(ERROR_MESSAGE_SET_CONSOLE_HANDLER_FAILED);
        return 1;
    }

    // Register cleanup function for SIGINT (e.g., Ctrl+C)
    signal(SIGINT, cleanup);

    

    // Create the input thread
    create_input_thread(&input_thread_handle, &sched);

    // Create the task execution thread
    create_task_thread(&task_thread_handle, &sched);

    // Wait for threads to finish (they run indefinitely in this case)
    WaitForSingleObject(input_thread_handle, INFINITE);
    WaitForSingleObject(task_thread_handle, INFINITE);

    // Clean up resources (in case the program reaches here)
    cleanup_resources();

    return 0;
}
