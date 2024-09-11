import random

# הגרלת מספר בין 10 ל-50
upper_limit = random.randint(10, 50)

# פתיחת קובץ לכתיבה
with open("output.txt", "w") as file:
    for _ in range(upper_limit):
        # הגרלת מספר בין -50 ל-20
        num1 = random.randint(-50, 20)
        # הגרלת מספר בין 100 ל-1000
        num2 = random.randint(100, 1000)

        # כתיבת 2 השורות לקובץ
        file.write(f"{num1}\n")
        file.write(f"{num2}\n")

print("הקובץ נכתב בהצלחה!")
