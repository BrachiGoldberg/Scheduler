
#include <math.h>
#include "RealTimeTask.h"
struct real_time_task* create_real_time_task(int priority, double execution_time, long double weight) {
    ID++;
    struct real_time_task* new_task = (struct real_time_task*)malloc(sizeof(struct real_time_task));
    new_task->id = ID;
    new_task->remaining_time = execution_time;
    new_task->weight = weight;
    return new_task;
}
void free_real_time_task(struct real_time_task* real_time_task) {
    free(real_time_task);
}