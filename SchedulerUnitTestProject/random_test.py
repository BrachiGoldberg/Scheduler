import random

# Generate a random number between 10 and 50
upper_limit = random.randint(10, 50)

# Open file for writing
with open("output.txt", "w") as file:
    for _ in range(upper_limit):
        # Generate a random number between -50 and 20
        num1 = random.randint(-50, 20)
        # Generate a random number between 100 and 1000
        num2 = random.randint(100, 1000)

        # Write the 2 lines to the file
        file.write(f"{num1}\n")
        file.write(f"{num2}\n")

print("File written successfully!")
