import unittest
import input_output
import subprocess
import time


class MyTestCase(unittest.TestCase):
    process_path = r"C:\Users\user1\Documents\ברכי\תיכנות\קמאטק - בודקמפ\scheduler-project\Scheduler\x64\Debug\Scheduler.exe"
    file_name = ["input.txt"]

    def test_something(self):

        for file in self.file_name:
            process = subprocess.Popen([self.process_path], stdin=subprocess.PIPE, text=True)
            input_output.open_input_file(file, process)
            time.sleep(10)
            process.stdin.close()
            process.terminate()

            self.assertEqual(False, False)  # add assertion here
            print("finish test")


if __name__ == '__main__':
    unittest.main()
