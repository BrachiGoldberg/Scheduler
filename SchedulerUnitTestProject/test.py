import unittest
import input_output
import subprocess
import time


class MyTestCase(unittest.TestCase):
    process_path = r"C:\Users\WIN 10\Desktop\בוטקמפ\ניסוי\Scheduler\x64\Debug\Scheduler.exe"
    file_name = ["output.txt"]
    process = None

    def create_process(self):
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


if __name__ == '__main__':
    unittest.main()
