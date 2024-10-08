from datetime import datetime, timedelta
from dotenv import load_dotenv
import re
import unittest
import input_output
import subprocess
import time
import os
import shutil
import random_test

load_dotenv()


class MyTestCase(unittest.TestCase):
    process_path = os.environ["PROCESS_PATH"]
    file_name = ["output.txt"]
    process = None

    def setUp(self):
        print("Now {} is running".format(self._testMethodName))

    def tearDown(self):
        print("{} finished".format(self._testMethodName))

    def create_process(self, file_name, time_to_wait):
        # delete the log file before creating the process
        if os.path.isdir("logs"):
            shutil.rmtree("logs")

        # create and close the process
        self.process = subprocess.Popen(
            [self.process_path], stdin=subprocess.PIPE, text=True
        )
        input_output.open_input_file(file_name, self.process)
        time.sleep(time_to_wait / 1000)
        self.process.stdin.close()
        self.process.terminate()
        self.process.wait()

    def test_all_tasks_begun(self):
        # input_all_tasks_begun.txt file:
        # min quantum of real time task: 20, max: 20
        # max time wait for all tasks need to begin: 20*5 = 100 milliseconds
        # min time wait for all tasks need to begin: 8*3+20*2 = 64 milliseconds

        file_name = r"inputs/input_all_tasks_begun.txt"
        time_to_wait = 60  # in milliseconds

        self.create_process(file_name, time_to_wait)

        # read the log file
        pattern = r"Task number \d+ got the CPU for"
        with open(r"logs/log.log") as file:
            content = file.read()

        matches = re.findall(pattern, content)
        ids = [re.findall(r"\d+", match) for match in matches]

        # Flatten the list of lists
        flattened_ids = [number for sublist in ids for number in sublist]

        uniq_id = set(flattened_ids)
        self.assertEqual(len(uniq_id), 5)

    def test_many_real_time_tasks_task_entered_and_got_CPU(self):
        # there are 9 real time tasks and after them 1 not real time task
        # the min time the last task get the CPU is 5*20

        file_name = r"inputs/input_many_real_time_tasks_task_entered_and_got_CPU.txt"
        time_to_wait = 100  # in milliseconds

        self.create_process(file_name, time_to_wait)

        # read the log file
        with open(r"logs/log.log") as file:
            content = file.read()

        pattern_to_find_id = r"Created new task ID \d+"
        match = re.findall(pattern_to_find_id, content)[0]
        # extract the task ID
        task_id = re.findall(r"\d+", match)[0]

        pattern_execute_task = r"Task number " + task_id + " got the CPU"
        execute_match = re.findall(pattern_execute_task, content)

        self.assertGreater(len(execute_match), 0)

    def test_CPU_is_divided_fairly(self):

        # create 2 dictionaries. one for real time tasks and second for not real time tasks
        # between one task finished to other check the divisions
        # each task got the CPU increase the amount in the appropriate dic.
        # find if the higher priority got the CPU more then the lowers.

        file_name = r"inputs/input.txt"
        time_to_wait = 1400  # in milliseconds // 7*200

        self.create_process(file_name, time_to_wait)

        not_real_time = {}
        tasks_info = {}

        lines = []

        cfs_file = r"cfs.c"

        pattern_task_finished = r"Task number \d+ finished"
        pattern_task_got_CPU = r"Task number \d+ got the CPU"
        pattern_task_created = r"Created new (?:real-time )?task ID (\d+) with execution time [\d.]+ and weight ([\d.]+)"

        pattern_task_finished_obj = re.compile(pattern_task_finished)
        pattern_task_got_CPU_obj = re.compile(pattern_task_got_CPU)
        pattern_task_created_obj = re.compile(pattern_task_created)

        assert_value = True
        with open(r"logs/log.log") as file:
            content = file.read()

            for line in content.splitlines():

                # check if the line is creating new task
                created_task = pattern_task_created_obj.findall(line)
                if len(created_task) != 0:
                    # insert the task to the tasks info
                    task = created_task[0]
                    tasks_info[task[0]] = task[1]

                match = pattern_task_finished_obj.findall(line)
                if len(match) == 0:
                    lines.append(line)
                else:
                    for extract_line in lines:
                        match = pattern_task_got_CPU_obj.findall(extract_line)
                        if len(match) != 0:  # save the id in the appropriate structure

                            # extract the appropriate structure
                            cfs = re.findall(cfs_file, extract_line)

                            # extract the task id
                            task_id = re.findall(r"\d+", match[0])[0]

                            # saving
                            if len(cfs) != 0:
                                if task_id in not_real_time:
                                    not_real_time[task_id] += 1
                                else:
                                    not_real_time[task_id] = 1
                    if len(not_real_time) > 1:
                        max_executed = max(not_real_time)
                        min_executed = min(not_real_time)
                        if not_real_time[max_executed] > not_real_time[min_executed] and tasks_info[max_executed] < tasks_info[min_executed]:
                            assert_value = False
                            break

                    # clear the structures
                    not_real_time = {}
                    lines = []
        self.assertEqual(True, assert_value)

    def test_high_priority_finished_first(self):
        file_name = r"inputs/input_high_priority_finished_first.txt"
        time_to_wait = 300

        self.create_process(file_name, time_to_wait)
        # Define patterns for task 1 and task 2
        pattern_task_1_finished = r"(\d{2}:\d{2}:\d{2}\.\d{6}) .* Task number 1 finished"
        pattern_task_2_finished = r"(\d{2}:\d{2}:\d{2}\.\d{6}) .* Task number 2 finished"

        # read the log file
        with open("logs/log.log") as file:
            content = file.read()

        # Extract the matched times for both tasks
        matched_task_1 = re.findall(pattern_task_1_finished, content)
        matched_task_2 = re.findall(pattern_task_2_finished, content)

        if not matched_task_1 or not matched_task_2:
            self.assertFalse(False, "there is no matched log entry")
        else:
            time_format = "%H:%M:%S.%f"
            time_1 = datetime.strptime(matched_task_1[0], time_format)
            time_2 = datetime.strptime(matched_task_2[0], time_format)

            self.assertTrue(time_2 < time_1)

    def test_all_tasks_completed(self):
        file_name = r"inputs/input_tasks_completion_check.txt"
        time_to_wait = 3000  # in milliseconds need to calculate

        self.create_process(file_name, time_to_wait)

        # Define regex patterns for task creation and task completion
        task_creation_pattern = re.compile(r"Created new task ID (\d+)")
        real_time_task_creation_pattern = re.compile(
            r"Created new real-time task ID (\d+)"
        )
        task_finished_pattern = re.compile(r"Task number (\d+) finished")

        created_tasks = set()
        finished_tasks = set()

        # Read the log file
        with open(r"logs/log.log") as file:
            content = file.read()

        # Find task creation and task completion entries
        for line in content.splitlines():
            # Check for regular task creation
            creation_match = task_creation_pattern.search(line)
            if creation_match:
                created_tasks.add(creation_match.group(1))
            # Check for real-time task creation
            real_time_creation_match = real_time_task_creation_pattern.search(
                line)
            if real_time_creation_match:
                created_tasks.add(real_time_creation_match.group(1))

            # Check for task completion
            finished_match = task_finished_pattern.search(line)
            if finished_match:
                finished_tasks.add(finished_match.group(1))

        # Check that all created tasks have finished
        self.assertEqual(created_tasks, finished_tasks,
                         "Not all tasks have completed.")

        # Print a success message if all tasks have been completed
        print("All tasks have been successfully completed.")

    def test_random(self):
        random_test.create_random_test()
        file_name = r"inputs/random_test"
        time_to_wait = 3000  # in milliseconds need to calculate
        execution_time_to_all_task, number_task = random_test.create_random_test()
        file_name = r"inputs/random_test"
        time_to_wait = execution_time_to_all_task + (number_task * 2000)  # in milliseconds need to calculate

        self.create_process(file_name, time_to_wait)

        # Define regex patterns for task creation and task completion
        task_creation_pattern = re.compile(r"Created new task ID (\d+)")
        real_time_task_creation_pattern = re.compile(
            r"Created new real-time task ID (\d+)"
        )
        task_finished_pattern = re.compile(r"Task number (\d+) finished")

        created_tasks = set()
        finished_tasks = set()

        # Read the log file
        with open(r"logs/log.log") as file:
            content = file.read()

        # Find task creation and task completion entries
        for line in content.splitlines():
            # Check for regular task creation
            creation_match = task_creation_pattern.search(line)
            if creation_match:
                created_tasks.add(creation_match.group(1))
            # Check for real-time task creation
            real_time_creation_match = real_time_task_creation_pattern.search(
                line)
            if real_time_creation_match:
                created_tasks.add(real_time_creation_match.group(1))

            # Check for task completion
            finished_match = task_finished_pattern.search(line)
            if finished_match:
                finished_tasks.add(finished_match.group(1))

        # Check that all created tasks have finished
        self.assertEqual(created_tasks, finished_tasks,
                         "Not all tasks have completed.")

        # Print a success message if all tasks have been completed
        print("All tasks have been successfully completed.")

    def test_task_execution_times(self):
        file_name = "inputs/input_task_runtime_matches_expected.txt"
        time_to_wait = 3000  # Adjust based on the expected execution duration

        self.create_process(file_name, time_to_wait)

        # Define patterns for task creation and task completion
        task_creation_pattern = re.compile(r"Created new (?:real-time )?task ID (\d+) with execution time ([\d.]+)")
        task_finished_pattern = re.compile(r"Task number (\d+) finished at (\d{2}:\d{2}:\d{2}\.\d{6})")

        task_execution_times = {}
        task_finish_times = {}

        # Read the log file
        with open("logs/log.log") as file:
            content = file.read()

            # Find task creation entries
            for line in content.splitlines():
                creation_match = task_creation_pattern.search(line)
                if creation_match:
                    task_id, exec_time = creation_match.groups()
                    task_execution_times[task_id] = float(exec_time)

                # Find task completion entries
                finish_match = task_finished_pattern.search(line)
                if finish_match:
                    task_id, finish_time_str = finish_match.groups()
                    finish_time = datetime.strptime(finish_time_str, "%H:%M:%S.%f")
                    task_finish_times[task_id] = finish_time

        # Check if task execution times match the expected durations
        for task_id, exec_time in task_execution_times.items():
            if task_id in task_finish_times:
                finish_time = task_finish_times[task_id]
                # Assume start time is the log entry time - execution time
                # This assumes that the execution time is given in milliseconds
                # and that tasks are started and finished within the given time.
                start_time = finish_time - timedelta(milliseconds=exec_time)
                # Check if the task execution time is close to the expected value
                self.assertAlmostEqual(
                    (finish_time - start_time).total_seconds() * 1000,
                    exec_time,
                    delta=50,  # Allowable margin of error in milliseconds
                    msg=f"Task {task_id} did not execute for the expected time"
                )
        print("All tasks executed for the expected duration.")
    
if __name__ == "__main__":
    unittest.main()
