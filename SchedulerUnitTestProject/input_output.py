
import time
import random


def open_input_file(file_name, process):
    # open the input file
    with open(file_name, "r") as file:

        while True:
            num_lines = random.randint(1, 5) * 2

            lines = [file.readline() for _ in range(num_lines)]

            if not any(lines):
                break

            process.stdin.writelines(lines)
            process.stdin.flush()
            wait_time = random.uniform(500, 2000) / 1000
            print(f"Read {num_lines} lines. Waiting for {wait_time * 1000:.0f} milliseconds...")
            time.sleep(wait_time)
