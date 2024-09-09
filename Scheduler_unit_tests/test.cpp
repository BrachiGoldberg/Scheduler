#define TEST_S

#include "pch.h"

TEST(TestCaseName, TestName) {

	//scheduler sched;
	//initial_all_structs(&sched);

	//new_task_arrival(10, 100, &sched);
	//new_task_arrival(5, 80, &sched);
	//new_task_arrival(0, 200, &sched);

	//HANDLE task_thread_handle;
	//create_task_thread(&task_thread_handle, &sched);

	//Sleep(420);
	//EXPECT_EQ(sched.tasks_tree->num_of_tasks, 0);
}
int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
}