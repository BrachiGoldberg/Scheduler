#include <windows.h>
#include "scheduler.h"
#include "mutex.h"
int main() {
    scheduler sched;
    // Initialize the scheduler and other necessary components
    sched.tasks_tree=initial_rb_tree();
    void initialize_queue(struct real_time_task_queue* queue);
    create_tree_mutex();
    create_queue_mutex();

    

    HANDLE input_thread_handle, task_thread_handle;

    // Create the input thread
    input_thread_handle = CreateThread(
        NULL,                  // Default security attributes
        0,                     // Default stack size
        input_thread,          // Thread function
        &sched,                // Argument to thread function
        0,                     // Default creation flags
        NULL                   // Pointer to receive thread ID
    );

    if (input_thread_handle == NULL) {
        printf("Failed to create input thread\n");
        return 1;
    }

    // Create the task execution thread
    task_thread_handle = CreateThread(
        NULL,                  // Default security attributes
        0,                     // Default stack size
        task_thread,           // Thread function
        &sched,                // Argument to thread function
        0,                     // Default creation flags
        NULL                   // Pointer to receive thread ID
    );

    if (task_thread_handle == NULL) {
        printf("Failed to create task thread\n");
        return 1;
    }

    // Wait for threads to finish (they run indefinitely in this case)
    WaitForSingleObject(input_thread_handle, INFINITE);
    WaitForSingleObject(task_thread_handle, INFINITE);

    // Clean up resources
    CloseHandle(input_thread_handle);
    CloseHandle(task_thread_handle);
    CloseHandle(queue_mutex);
    CloseHandle(tree_mutex);
    free_queue(sched.queue);
    free_struct_rb_tree(sched.tasks_tree);
    return 0;
}