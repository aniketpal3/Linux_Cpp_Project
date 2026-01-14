#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <unordered_map>
#include <regex>

// Shared data
std::queue<std::string> logQueue;
std::mutex queueMutex;
std::condition_variable cv;

std::unordered_map<std::string, int> logCount;
std::mutex countMutex;

// Validate log format
bool parseLog(const std::string& line, std::string& level) {
    std::regex pattern(R"(\[.*\]\s(INFO|WARNING|ERROR|DEBUG)\s.*)");
    std::smatch match;
    if (std::regex_match(line, match, pattern)) {
        level = match[1];
        return true;
    }
    return false;
}

// Thread 1: Read log file (batch mode - beginner safe)
void logReader() {
    std::ifstream file("logs/app.log");
    if (!file.is_open()) {
        std::cerr << "ERROR: logs/app.log not found\n";
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::lock_guard<std::mutex> lock(queueMutex);
        logQueue.push(line);
        cv.notify_one();
    }
}

// Thread 2: Process logs
void logProcessor() {
    std::ofstream errorFile("output/error.log", std::ios::app);

    while (true) {
        std::unique_lock<std::mutex> lock(queueMutex);
        if (logQueue.empty())
            break;

        std::string line = logQueue.front();
        logQueue.pop();
        lock.unlock();

        std::string level;
        if (parseLog(line, level)) {
            {
                std::lock_guard<std::mutex> cLock(countMutex);
                logCount[level]++;
            }
            if (level == "ERROR") {
                errorFile << line << std::endl;
            }
        } else {
            std::cerr << "Invalid log format: " << line << std::endl;
        }
    }

    // Print summary
    std::cout << "\n--- Log Summary ---\n";
    for (auto& p : logCount) {
        std::cout << p.first << ": " << p.second << std::endl;
    }
}

int main() {
    std::thread reader(logReader);
    reader.join();   // wait until logs are read

    std::thread processor(logProcessor);
    processor.join(); // now process logs

    std::cout << "Application exited cleanly\n";
    return 0;
}

