#include <iostream>
#include "task.h"
#include <sstream>
#include <vector>

using namespace std;

uint8_t getNextFreeId(const vector<Task>& tasks) {
    uint8_t n_id = 0;
    for (const auto& t : tasks) {
        if (t.m_id > n_id) {
            n_id = t.m_id;
        }
    }
    return n_id + 1;
}

size_t indexOfTaskById(const uint8_t id, const vector<Task>& tasks) {
    for (int i = 0; i < tasks.size(); i++) {
        if (tasks[i].m_id == id) {
            return i;
        }
    }
    return -1;
}

int main() {
    cout << "Welcome to task-tool!" << endl;

    vector<Task> tasks{};
    string input;

    while (true) {
        cout << "Enter menu command (h = help; q = quit)" << endl;
        getline(cin, input);
        istringstream iss(input);
        vector<string> args;
        string token;

        while (iss >> token) {
            args.push_back(token);
        }

        if (args.empty()) {
            continue;
        }

        string command = args[0];
        if (command == "q") {
            cout << "# EXIT PROGRAM #" << endl;
            break;
        }
        if (command == "h") {
            cout << "# HELP #" << endl;
            cout << "- add TITLE STATE:         Add new task" << endl;
            cout << "- edit ID TITLE STATE:     Edit task by id" << endl;
            cout << "- delete ID:               Delete task by id" << endl;
            cout << "- list:                    List all tasks" << endl;
            cout << "- h:                       Show help" << endl;
            cout << "- d:                       Generate demo entries" << endl;
            cout << "- q:                       Quit program" << endl;
            continue;
        }
        if (command == "d") {
            cout << "# DEMO #" << endl;
            tasks.push_back({getNextFreeId(tasks), "Cleaning", "OPEN"});
            tasks.push_back({getNextFreeId(tasks), "Cooking", "DOING"});
            tasks.push_back({getNextFreeId(tasks), "Washing", "DONE"});
            continue;
        }

        if (command == "add") {
            cout << "# ADD TASK #" << endl;
            if (args.size() == 3) {
                try {
                    tasks.push_back({getNextFreeId(tasks), args[1], args[2]});
                }
                catch (const exception& e) {
                    cout << "Error: while adding" << endl;
                }
            }
            else {
                cout << "Error: command format not as expected: add TITLE STATE" << endl;
            }
        }
        else if (command == "edit") {
            cout << "# EDIT TASK #" << endl;
            if (args.size() == 4) {
                try {
                    const uint8_t id = stoi(args[1]);
                    const size_t idx = indexOfTaskById(id, tasks);

                    if (idx != -1) {
                        tasks[idx].m_name = args[2];
                        tasks[idx].m_state = args[3];
                    }
                    else {
                        cout << "Error: Task with id (" << static_cast<unsigned>(id) << ") not found." << endl;
                    }
                }
                catch (const exception& e) {
                    cout << "Error: while editing" << endl;
                }
            }
            else {
                cout << "Error: command format not as expected: edit ID TITLE STATE" << endl;
            }
        } else if (command == "delete") {
            cout << "# DELETE TASK #" << endl;
            if (args.size() == 2) {
                try {
                    const uint8_t id = stoi(args[1]);
                    const size_t idx = indexOfTaskById(id, tasks);

                    if (idx != -1) {
                        tasks.erase(tasks.begin() + idx);
                    }
                    else {
                        cout << "Error: Task with id (" << static_cast<unsigned>(id) << ") not found." << endl;
                    }
                }
                catch (const exception& e) {
                    cout << "Error: while deleting" << endl;
                }
            }
            else {
                cout << "Error: command format not as expected: delete ID" << endl;
            }
        }
        else if (command == "list") {
            cout << "# LIST TASKS #" << endl;
            if (tasks.empty()) {
                cout << "No tasks" << endl;
            }
            else {
                cout << "Tasks:" << endl;
                for (auto t : tasks) {
                    cout << t << endl;
                }
            }
        }
    }

    return 0;
}
