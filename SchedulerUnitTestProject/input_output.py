import time
import random

def open_input_file(file_name, process):
    # open the input file
    try:
        with open(file_name, "r") as file:
            while True:
                num_lines = random.randint(1, 5) * 2  # Read a random number of lines (1-5 pairs)
                lines = [file.readline() for _ in range(num_lines)]

                if not any(lines):  # Break if we reach the end of the file
                    break

                # Write the lines to the process input
                process.stdin.writelines(lines)  
                process.stdin.flush()  # Ensure all input is flushed to the process

                # Wait time between sending input
                wait_time = random.uniform(0.5, 2.0)  # seconds
                print(f"Read {num_lines} lines. Waiting for {wait_time * 1000:.0f} milliseconds...")
                time.sleep(wait_time)  # Simulate delay before sending more input

    except FileNotFoundError:
        print(f"Error: The file '{file_name}' was not found.")
    except Exception as e:
        print(f"An error occurred: {e}")
