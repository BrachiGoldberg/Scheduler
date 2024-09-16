import random


def create_random_test() -> object:
    # Generate a random number between 10 and 50
    upper_limit = random.randint(10, 20)

    execution_time_to_all_task = 0
    number_task = upper_limit

    # Open file for writing
    with open("inputs/random_test", "w") as file:
        for _ in range(upper_limit):
            # Generate a random number between -50 and 20
            priority = random.randint(-50, 20)
            # Generate a random number between 100 and 1000
            execution_time = random.randint(100, 1000)
            execution_time_to_all_task += execution_time
            # Write the 2 lines to the file
            file.write(f"{priority}\n")
            file.write(f"{execution_time}\n")

    return execution_time_to_all_task, number_task

