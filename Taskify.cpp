// Taskify - Simple CLI Task Manager
// Author: CuneytKose

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>

struct Task {
    int id;
    std::string description;
    bool completed;

    std::string to_string() const {
        return std::to_string(id) + "|" + description + "|" + (completed ? "1" : "0");
    }

    static Task from_string(const std::string& line) {
        Task task;
        std::istringstream ss(line);
        std::string token;

        std::getline(ss, token, '|');
        task.id = std::stoi(token);
        std::getline(ss, task.description, '|');
        std::getline(ss, token, '|');
        task.completed = (token == "1");

        return task;
    }
};

std::vector<Task> load_tasks(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<Task> tasks;
    std::string line;

    while (std::getline(file, line)) {
        if (!line.empty()) {
            tasks.push_back(Task::from_string(line));
        }
    }

    return tasks;
}

void save_tasks(const std::vector<Task>& tasks, const std::string& filename) {
    std::ofstream file(filename, std::ios::trunc);
    for (const auto& task : tasks) {
        file << task.to_string() << "\n";
    }
}

void add_task(const std::string& filename, const std::string& description) {
    auto tasks = load_tasks(filename);
    int next_id = tasks.empty() ? 1 : tasks.back().id + 1;
    Task new_task{next_id, description, false};
    tasks.push_back(new_task);
    save_tasks(tasks, filename);
    std::cout << "[+] Task added with ID " << next_id << std::endl;
}

void list_tasks(const std::string& filename) {
    auto tasks = load_tasks(filename);
    if (tasks.empty()) {
        std::cout << "No tasks found." << std::endl;
        return;
    }

    for (const auto& task : tasks) {
        std::cout << task.id << " - " << task.description << " [" << (task.completed ? "Done" : "Pending") << "]\n";
    }
}

void mark_done(const std::string& filename, int id) {
    auto tasks = load_tasks(filename);
    bool found = false;

    for (auto& task : tasks) {
        if (task.id == id) {
            task.completed = true;
            found = true;
            break;
        }
    }

    if (found) {
        save_tasks(tasks, filename);
        std::cout << "[✔] Task " << id << " marked as done." << std::endl;
    } else {
        std::cout << "[!] Task ID not found." << std::endl;
    }
}

int main(int argc, char* argv[]) {
    const std::string filename = "tasks.txt";

    if (argc < 2) {
        std::cout << "Usage: ./Taskify <add/list/done> [args]\n";
        return 1;
    }

    std::string command = argv[1];

    if (command == "add" && argc >= 3) {
        std::ostringstream desc;
        for (int i = 2; i < argc; ++i) {
            desc << argv[i];
            if (i < argc - 1) desc << " ";
        }
        add_task(filename, desc.str());
    } else if (command == "list") {
        list_tasks(filename);
    } else if (command == "done" && argc == 3) {
        int id = std::stoi(argv[2]);
        mark_done(filename, id);
    } else {
        std::cout << "Invalid command or arguments.\n";
    }

    return 0;
}
