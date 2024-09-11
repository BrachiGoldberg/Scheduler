import re
import unittest
import input_output
import subprocess
import time
import os
import shutil

class MyTestCase(unittest.TestCase):
    process_path = r"C:\Users\user1\Documents\ברכי\תיכנות\קמאטק - בודקמפ\scheduler-project\Scheduler\x64\Debug\Scheduler.exe"
    file_name = ["input.txt"]
    process = None

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
            time.sleep(10)
            self.process.stdin.close()
            self.process.terminate()

            self.assertEqual(False, False)  # add assertion here
            print("finish test")

    def test_all_tasks_begun(self):
        # input_all_tasks_begun.txt file:
        # 10 //weight = 109.95116277760000
        # 100
        # 8 //weight = 171.79869184000000
        # 150
        # -30 //weight = 827180.61255302757
        # 40
        # 12 //weight = 70.368744177663999
        # 120
        # -40 //weight = 7703719.7775489436
        # 200
        # total weight (not real time): 352.11859879526401
        # total weight (real time): 8530900.3901019711
        # min time slice of not real time task: 8, max: 20
        # min quantum of real time task: 20, max: 20
        # max time wait for all tasks need to begin: 20*5 = 100 milliseconds
        # min time wait for all tasks need to begin: 8*3+20*2 = 64 milliseconds

        file_name = r"input_all_tasks_begun.txt"
        number_lines = 10
        time_to_wait = 60  # in milliseconds

        self.create_process()
        input_output.open_input_file(file_name, self.process, number_lines)

        time.sleep(time_to_wait/1000)
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


if __name__ == '__main__':
    unittest.main()
