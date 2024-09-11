import re
import unittest
import input_output
import subprocess
import time
import os
import shutil


class MyTestCase(unittest.TestCase):
    process_path = r"C:\Users\user1\Documents\ברכי\תיכנות\קמאטק - בודקמפ\scheduler-project\Scheduler\x64\Debug\Scheduler.exe"
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

        file_name = r"input.txt"
        time_to_wait = 1400  # in milliseconds // 7*200

        self.create_process()
        input_output.open_input_file(file_name, self.process)

        time.sleep(time_to_wait / 1000)
        self.process.stdin.close()
        self.process.terminate()

        real_time = {}
        not_real_time = {}

        lines = []

        round_robin_file = r"round_robin.c"
        cfs_file = r"cfs.c"

        pattern_task_finished = r"Task number \d+ finished"
        pattern_task_got_CPU = r"Task number \d+ got the CPU"

        pattern_task_finished_obj = re.compile(pattern_task_finished)
        pattern_task_got_CPU_obj = re.compile(pattern_task_got_CPU)

        with open(r"logs/log.log") as file:
            for line in file:
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
                            else:
                                if task_id in real_time:
                                    real_time[task_id] += 1
                                else:
                                    real_time[task_id] = 1

                    print("the dict of real time tasks is:")
                    print(real_time)
                    print("the dict of not real time tasks is:")
                    print(not_real_time)

                    # clear the structures
                    real_time = {}
                    not_real_time = {}

                    lines = []

        print(self.process)


if __name__ == '__main__':
    unittest.main()
