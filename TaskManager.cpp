#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

// Task structure to hold a description and completion status
struct Task {
    string description;
    bool completed;

    // Constructor initializes a new task as incomplete
    Task(string desc) : description(desc), completed(false) {}
};

// Task Manager Class
class TaskManager {
private:
    vector<Task> tasks; // Stores all tasks in memory
    string filename; // User-defined file to store tasks

public:
    // Constructor loads tasks from a file at initialization
    TaskManager(const string& file) : filename(file) {
        loadTasks();
    }

    // Function to get valid integer input within a given range
    int getValidIntInput(const string& prompt, int min, int max) {
        int input;
        while (true) {
            cout << prompt;
            cin >> input;
    
            // Check if input is invalid (not a number or out of range)
            if (cin.fail() || input < min || input > max) {
                cin.clear(); // Clear error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                cout << "\nInvalid input. Please enter a number between " << min << " and " << max << ".\n";
            } else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer to avoid issues
                return input;
            }
        }
    }

    // Add a new task to the list
    void addTask() {
        string desc;
        cout << "\nEnter task description: ";
        getline(cin, desc); // Read entire line, allowing spaces in task names
        tasks.emplace_back(desc);
        cout << "Task added successfully!\n";
        saveTasks(); // Save updated task list to file
    }

    // Display all tasks with their status
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

    // Remove a task based on user input
    void removeTask() {
        viewTasks(); // Show tasks before asking for input
        if (tasks.empty()) return;

        int index = getValidIntInput("\nEnter task number to remove: ", 1, tasks.size());
        tasks.erase(tasks.begin() + index - 1); // Remove task (convert 1-based index to 0-based)
        cout << "Task removed successfully!\n";
        saveTasks();
    }

    // Mark a selected task as completed
    void markCompleted() {
        viewTasks();
        if (tasks.empty()) return;

        int index = getValidIntInput("\nEnter task number to mark as completed: ", 1, tasks.size());
        tasks[index - 1].completed = true; // Convert 1-based input to 0-based index
        cout << "Task marked as completed!\n";
        saveTasks();
    }

    // Save all tasks to the file (overwrites the existing file)
    void saveTasks() {
        ofstream file(filename);
        if (!file) {
            cout << "Error saving tasks.\n";
            return;
        }
        for (const auto& task : tasks) {
            file << task.completed << "|" << task.description << "\n"; // Format: completed_status|description
        }
        file.close();
    }

    // Load tasks from a file at startup
    void loadTasks() {
        ifstream file(filename);
        if (!file) {
            cout << "No existing tasks file found. A new file will be created with the filename provided.\n";
            return;
        } 

        string line;
        while (getline(file, line)) {
            size_t delimiter = line.find('|'); // Find separator between completed status and description
            if (delimiter != string::npos) {
                bool completed = (line.substr(0, delimiter) == "1"); // Convert "1" to true, "0" to false
                string description = line.substr(delimiter + 1);
                tasks.emplace_back(description);
                tasks.back().completed = completed;
            }
        }
        file.close();

        cout << "File loaded! File will automatically be updated as you add, complete, and remove tasks.\n";
    }

    // Display the main menu and handle user choices
    void showMenu() {
        int choice;
        do {
            cout << "\nTo-Do List\n";
            cout << "1. Add Task\n";
            cout << "2. View Tasks\n";
            cout << "3. Remove Task\n";
            cout << "4. Mark Task as Completed\n";
            cout << "5. Exit\n";

            choice = getValidIntInput("Choose an option: ", 1, 5); // Ensure valid user input

            switch (choice) {
                case 1: addTask(); break;
                case 2: viewTasks(); break;
                case 3: removeTask(); break;
                case 4: markCompleted(); break;
                case 5: cout << "\nExiting... Goodbye!\n\n"; break;
            }
        } while (choice != 5); // Keep running until user chooses to exit
    }
};

// Main Function
int main() {
    string filename;

    cout << "\nWelcome to the Task Manager!\n";
    cout << "\nEnter the filename to load tasks from: ";
    cin >> filename;

    TaskManager taskManager(filename); // Initialize task manager with user-provided file
    taskManager.showMenu(); // Start the menu loop

    return 0;
}