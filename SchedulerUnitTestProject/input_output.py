import subprocess
import time
import random

#open the input file
with open(r"C:\Users\user1\Desktop\ProjectWestern\Scheduler\Scheduler\SchedulerUnitTestProject\input.txt", "r") as file:
    path = r"C:\Users\user1\Desktop\ProjectWestern\Scheduler\Scheduler\x64\Debug\Scheduler.exe"
    process = subprocess.Popen([path], stdin=subprocess.PIPE, text=True)

    while True:
        line_index = 0

        num_lines = random.randint(1, 5) * 2

        lines = [file.readline() for _ in range(num_lines)]

        if not any(lines):
            break

        process.stdin.writelines(lines)
        process.stdin.flush()
        wait_time = random.uniform(500, 2000) / 1000
        print(f"Read {num_lines} lines. Waiting for {wait_time * 1000:.0f} milliseconds...")
        time.sleep(wait_time)

    time.sleep(20)
    process.stdin.close()
    process.terminate()
    print("finish test")
input("Press Enter to exit...")
