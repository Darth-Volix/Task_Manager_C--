#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

// Task structure
struct Task {
    string description;
    bool completed;

    Task(string desc) : description(desc), completed(false) {}
};

// Task Manager Class
class TaskManager {
private:
    vector<Task> tasks;
    string filename; // User-defined file to store tasks

public:
    TaskManager(const string& file) : filename(file) {
        loadTasks();
    }

    // Function to get valid integer input
    int getValidIntInput(const string& prompt, int min, int max) {
        int input;
        while (true) {
            cout << prompt;
            cin >> input;

            if (cin.fail() || input < min || input > max) {
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                cout << "\nInvalid input. Please enter a number between " << min << " and " << max << ".\n";
            } else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
                return input;
            }
        }
    }

    // Add a task
    void addTask() {
        cin.ignore(); // Ignore leftover newline
        string desc;
        cout << "\nEnter task description: ";
        getline(cin, desc);
        tasks.emplace_back(desc);
        cout << "Task added successfully!\n";
        saveTasks();
    }

    // View all tasks
    void viewTasks() {
        if (tasks.empty()) {
            cout << "\nNo tasks available.\n";
            return;
        }
        cout << "\nYour Tasks:\n";
        for (size_t i = 0; i < tasks.size(); ++i) {
            cout << i + 1 << ". " << (tasks[i].completed ? "[X] " : "[ ] ") << tasks[i].description << "\n";
        }
    }

    // Remove a task
    void removeTask() {
        viewTasks();
        if (tasks.empty()) return;

        int index = getValidIntInput("\nEnter task number to remove: ", 1, tasks.size());
        tasks.erase(tasks.begin() + index - 1);
        cout << "Task removed successfully!\n";
        saveTasks();
    }

    // Mark task as completed
    void markCompleted() {
        viewTasks();
        if (tasks.empty()) return;

        int index = getValidIntInput("\nEnter task number to mark as completed: ", 1, tasks.size());
        tasks[index - 1].completed = true;
        cout << "Task marked as completed!\n";
        saveTasks();
    }

    // Save tasks to a file
    void saveTasks() {
        ofstream file(filename);
        if (!file) {
            cout << "Error saving tasks.\n";
            return;
        }
        for (const auto& task : tasks) {
            file << task.completed << "|" << task.description << "\n";
        }
        file.close();
    }

    // Load tasks from a file
    void loadTasks() {
        ifstream file(filename);
        if (!file) {
            cout << "No existing tasks file found. A new file will be created with the filename provided.\n";
            return;
        } 

        string line;
        while (getline(file, line)) {
            size_t delimiter = line.find('|');
            if (delimiter != string::npos) {
                bool completed = (line.substr(0, delimiter) == "1");
                string description = line.substr(delimiter + 1);
                Task task(description);
                task.completed = completed;
                tasks.push_back(task);
            }
        }
        file.close();

        cout << "File loaded! File will automatically be updated as you add, complete, and remove tasks.\n";
    }

    // Show menu
    void showMenu() {
        int choice;
        do {
            cout << "\nTo-Do List\n";
            cout << "1. Add Task\n";
            cout << "2. View Tasks\n";
            cout << "3. Remove Task\n";
            cout << "4. Mark Task as Completed\n";
            cout << "5. Exit\n";

            choice = getValidIntInput("Choose an option: ", 1, 5);

            switch (choice) {
                case 1: addTask(); break;
                case 2: viewTasks(); break;
                case 3: removeTask(); break;
                case 4: markCompleted(); break;
                case 5: cout << "\nExiting... Goodbye!\n\n"; break;
            }
        } while (choice != 5);
    }
};

// Main Function
int main() {
    string filename;

    cout << "\nWelcome to the Task Manager!\n";
    cout << "\nEnter the filename to load tasks from: ";
    cin >> filename;

    TaskManager taskManager(filename);
    taskManager.showMenu();

    return 0;
}