import re
import unittest
import input_output
import subprocess
import time
import os
import shutil


class MyTestCase(unittest.TestCase):
    process_path = r"C:\Users\WIN 10\Desktop\בוטקמפ\ניסוי\Scheduler\x64\Debug\Scheduler.exe"
    file_name = ["output.txt"]
    process = None

    def setUp(self):
        print("before {}".format(self._testMethodName))

    def tearDown(self):
        print("after {}".format(self._testMethodName))

    def create_process(self):
        # delete the log file before creating the process
        if os.path.isdir("logs"):
            shutil.rmtree("logs")

        # create the process
        self.process = subprocess.Popen([self.process_path], stdin=subprocess.PIPE, text=True)

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
        # input_all_tasks_begun.txt file:
        # min quantum of real time task: 20, max: 20
        # max time wait for all tasks need to begin: 20*5 = 100 milliseconds
        # min time wait for all tasks need to begin: 8*3+20*2 = 64 milliseconds

        file_name = r"inputs/input_all_tasks_begun.txt"
        # number_lines = 10
        time_to_wait = 60  # in milliseconds

        self.create_process()
        input_output.open_input_file(file_name, self.process)

        time.sleep(time_to_wait/1000)
        self.process.stdin.close()
        self.process.terminate()

        # read the log file
        pattern = r"Task number \d+ got the CPU for"
        with open(r"log.log") as file:
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
        # number_lines = 20
        time_to_wait = 100  # in milliseconds

        self.create_process()
        input_output.open_input_file(file_name, self.process)

        time.sleep(time_to_wait / 1000)
        self.process.stdin.close()
        self.process.terminate()

        # read the log file
        with open(r"log.log") as file:
            content = file.read()

        pattern_to_find_id = r"Created new task ID \d+"
        match = re.findall(pattern_to_find_id, content)[0]
        # extract the task ID
        task_id = re.findall(r"\d+", match)[0]

        pattern_execute_task = r"Task number "+task_id+" got the CPU"
        execute_match = re.findall(pattern_execute_task, content)

        self.assertGreater(len(execute_match), 0)


if __name__ == '__main__':
    unittest.main()
