#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// i need create todo list in c with terminal ui
// i want to add/remove/edit/view/complete tasks
// i want to mark tasks as completed
// i want to filter tasks by status (completed/incomplete)
// i want to sort tasks by due date
// i want to prioritize tasks
// i want to have a timer for each task
// i want to have a reminder for each task
// i want to have a notification system when a task is due
// i want to have a task history
// i want to have a search functionality
// i want to have a task statistics
// i want to have a task calendar

#define MAX_TASKS 100

enum TaskStatus {
    COMPLETED,
    INCOMPLETE
};

enum TaskPriority {
    HIGH,
    MEDIUM,
    LOW
};

struct Task {
    char title[100];
    char description[200];
    enum TaskPriority priority; // HIGH/MEDIUM/LOW
    enum TaskStatus status; // COMPLETED/INCOMPLETE
};

struct TodoList {
    struct Task tasks[MAX_TASKS];
    int taskCount;
    char name[100];
    char description[200];
};

void showTasks(struct TodoList* todoList) {
    printf("Task List: %s\n", todoList->name);
    for (int i = 0; i < todoList->taskCount; i++) {
        struct Task* task = &todoList->tasks[i];
        printf("%d. %s (%s) - %s\n", i + 1, task->title, task->status == COMPLETED? "Completed" : "Incomplete", task->description);
    }
    printf("\n");
    printf("Total tasks: %d\n", todoList->taskCount);
}

void addTask(struct TodoList* todoList) {
    if (todoList->taskCount >= MAX_TASKS) {
        printf("Maximum number of tasks reached.\n");
        return;
    }

    printf("Enter task title: \n");
    scanf("%s", todoList->tasks[todoList->taskCount].title);

    printf("Enter task description: \n");
    scanf("%s", todoList->tasks[todoList->taskCount].description);

    printf("Enter task priority (1 for HIGH, 2 for MEDIUM, 3 for LOW): \n");
    enum TaskPriority priorityInput;
    scanf("%d", &priorityInput);
    todoList->tasks[todoList->taskCount].priority = priorityInput == 1? HIGH : (priorityInput == 2? MEDIUM : LOW);

    enum TaskStatus status = INCOMPLETE;
    todoList->tasks[todoList->taskCount].status = status;

    todoList->taskCount++;
    printf("Task added successfully.\n");
}

void removeTask(struct TodoList* todoList) {
    if (todoList->taskCount == 0) {
        printf("No tasks to remove.\n");
        return;
    }

    printf("Enter task number to remove: ");
    int taskNumber;
    scanf("%d", &taskNumber);
    if (taskNumber < 1 || taskNumber > todoList->taskCount) {
        printf("Invalid task number.\n");
        return;
    }

    for (int i = taskNumber - 1; i < todoList->taskCount - 1; i++) {
        todoList->tasks[i] = todoList->tasks[i + 1];
    }
    todoList->taskCount--;
}

struct TodoList* createTodoList(const char* name, const char* description) {
    struct TodoList* todoList = malloc(sizeof(struct TodoList));
    if (todoList == NULL) {
        printf("Error: Failed to allocate memory for todo list.\n");
        return NULL;
    }
    strcpy(todoList->name, name);
    strcpy(todoList->description, description);
    todoList->taskCount = 0;
    return todoList;
}

int main() {
    struct TodoList* todoList = createTodoList("My Todo List", "This is my personal todo list.");
    while(1) {
        printf("Todo List Application\n");
        printf("1. Show tasks\n");
        printf("2. Add task\n");
        printf("3. Remove task\n");
        printf("4. Exit\n");

        int choice;
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                showTasks(todoList);
                break;
            case 2:
                addTask(todoList);
                break;
            case 3:
                removeTask(todoList);
                break;
            case 4:
                free(todoList);
                return EXIT_SUCCESS;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return EXIT_SUCCESS;
}
