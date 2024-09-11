import re
import unittest
import input_output
import subprocess
import time
import os
import shutil


class MyTestCase(unittest.TestCase):
    process_path = r"C:\Users\user1\Desktop\ProjectWestern\Scheduler\Scheduler\x64\Debug\Scheduler.exe"
    file_name = ["output.txt"]
    process = None

    def create_process(self):
        # delete the log file before creating the process
        if os.path.isdir("logs"):
            shutil.rmtree("logs")

        # create the process
        self.process = subprocess.Popen([self.process_path], stdin=subprocess.PIPE, text=True)

    # Commented out code
    
    def setUp(self):
        print("before {}".format(self._testMethodName))

    def tearDown(self):
        print("after {}".format(self._testMethodName))

    def test_something(self):
        for file in self.file_name:
            # create the process
            self.create_process()
            # read the input from the file, and send it to the process
            input_output.open_input_file(file, self.process)

            # wait time until terminate the process
            time.sleep(50)
            self.process.stdin.close()
            self.process.terminate()

            self.assertEqual(False, False)  # add assertion here

            print("finish test")

    def test_all_tasks_begun(self):
        file_name = r"inputs/input_all_tasks_begun.txt"
        time_to_wait = 60  # in milliseconds

        self.create_process()
        input_output.open_input_file(file_name, self.process)

        time.sleep(time_to_wait / 1000)
        self.process.stdin.close()
        self.process.terminate()

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
        file_name = r"inputs/input_many_real_time_tasks_task_entered_and_got_CPU.txt"
        time_to_wait = 100  # in milliseconds

        self.create_process()
        input_output.open_input_file(file_name, self.process)

        time.sleep(time_to_wait / 1000)
        self.process.stdin.close()
        self.process.terminate()

        # read the log file
        with open(r"logs/log.log") as file:
            content = file.read()

        pattern_to_find_id = r"Created new task ID \d+"
        match = re.findall(pattern_to_find_id, content)[0]
        task_id = re.findall(r"\d+", match)[0]

        pattern_execute_task = r"Task number " + task_id + " got the CPU"
        execute_match = re.findall(pattern_execute_task, content)

        self.assertGreater(len(execute_match), 0)
    

    def test_all_tasks_completed(self):
        file_name = r"inputs/input_tasks_completion_check.txt"
        time_to_wait = 100  # in milliseconds

        self.create_process()
        input_output.open_input_file(file_name, self.process)

        # Wait for the tasks to run and complete
        time.sleep(time_to_wait / 1000)
        self.process.stdin.close()
        self.process.terminate()
        self.process.wait()  

        # Define regex patterns for task creation and task completion
        task_creation_pattern = re.compile(r"Created new task ID (\d+)")
        real_time_task_creation_pattern = re.compile(r"Created new real-time task ID (\d+)")
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
            real_time_creation_match = real_time_task_creation_pattern.search(line)
            if real_time_creation_match:
                 created_tasks.add(real_time_creation_match.group(1))

            # Check for task completion
            finished_match = task_finished_pattern.search(line)
            if finished_match:
                finished_tasks.add(finished_match.group(1))

        # Check that all created tasks have finished
        self.assertEqual(created_tasks, finished_tasks, "Not all tasks have completed.")

        # Print a success message if all tasks have been completed
        print("All tasks have been successfully completed.")

if __name__ == '__main__':
    unittest.main()
