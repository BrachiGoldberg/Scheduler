def check_log_for_completed_tasks(log_file_path, tasks_file_path):
    # קריאת רשימת המשימות מקובץ המשימות
    tasks = set()
    with open(tasks_file_path, 'r') as tasks_file:
        for line in tasks_file:
            task = line.strip()
            if task:
                tasks.add(task)

    # קריאת קובץ הלוג ובדיקת האם כל המשימות הסתיימו
    completed_tasks = set()
    with open(log_file_path, 'r') as log_file:
        for line in log_file:
            for task in list(tasks):
                if task in line and 'finished' in line:
                    completed_tasks.add(task)

    # הצגת תוצאות
    tasks_not_completed = tasks - completed_tasks
    if not tasks_not_completed:
        print("All tasks have been completed successfully.")
    else:
        for task in tasks_not_completed:
            print(f"Task '{task}' was not completed.")

# דוגמת שימוש
if __name__ == "__main__":
    log_file_path = r'C:\Users\user1\Desktop\ProjectWestern\Scheduler\Scheduler\SchedulerUnitTestProject\log.log'
    tasks_file_path = r'C:\Users\user1\Desktop\ProjectWestern\Scheduler\Scheduler\SchedulerUnitTestProject\tasksfile.txt'
    
    check_log_for_completed_tasks(log_file_path, tasks_file_path)
