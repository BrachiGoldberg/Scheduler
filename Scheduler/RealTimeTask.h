#ifndef REAL_TIME_TASK_H
#define REAL_TIME_TASK_H
static int ID = 0;
struct real_time_task {
	long id;
	// int priority;               
	double quantum;
	long double weight;
	double remaining_time;
	double execution_time;
};
struct real_time_task* create_real_time_task(int priority, double execution_time, long double weight);
void free_real_time_task(struct real_time_task*);
#endif // REAL_TIME_TASK_H
