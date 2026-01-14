# 🖥️ Linux-Based Multi-Threaded Log Processing Service

## 🔹 Project Overview
This project is a **C++ application** that monitors and processes log files efficiently on Linux.  
It leverages **multi-threading** for concurrent log reading and processing and is fully **containerized using Docker** for portability.

> The application counts logs by type (INFO, ERROR, WARNING, DEBUG) and writes ERROR logs separately for easy monitoring.[TIMESTAMP] [LEVE


## 🌟 Key Features
- **Batch & Real-Time Log Processing:** Reads logs from a file and processes them in a thread-safe manner.
- **Multi-Threading:** Uses producer-consumer model with `std::thread` and `std::mutex`.
- **Log Categorization:** Counts logs by type.
- **Error Logging:** Writes all `ERROR` logs to a separate file (`output/error.log`).
- **Graceful Shutdown:** Handles Ctrl+C (`SIGINT`) cleanly.
- **Dockerized:** Runs in a container for portability and reproducibility.

## 📂 Log Format
All log entries must follow this format:

[TIMESTAMP] [LEVEL] Message

**Supported Levels:**
- INFO
- WARNING
- ERROR
- DEBU
**Example:**
[2025-01-10 11:00:01] ERROR Payment failed
[2025-01-10 10:25:30] INFO Application started

## 🏗️ Project Structure

Linux_C++_Log_Processor/
├── src/
│   └── main.cpp
├── logs/
│   └── app.log
├── output/
│   └── error.log
├── Dockerfile
├── README.md
└── log_processor

## ⚙️ How to Build & Run

### 🔹 Linux / WSL
# Compile the program
g++ -std=c++17 src/main.cpp -o log_processor -pthread

# Run the program
./log_processor
🔹 Using Docker

# Build Docker image
docker build -t log-processor .

# Run container with mounted logs and output directories
docker run --rm \
-v $(pwd)/logs:/app/logs \
-v $(pwd)/output:/app/output \
log-processor

Console Output:

makefile
--- Log Summary ---
INFO: 2
ERROR: 2
WARNING: 1
DEBUG: 2
Application exited cleanly
Error Log (output/error.log):

[2025-01-10 10:25:31] ERROR Database connection failed
[2025-01-10 11:00:01] ERROR Payment failed

🧠 Technologies & Concepts Used

C++17: Core language features, OOPs Principles.
Threads & Mutex: std::thread, std::mutex, std::condition_variable.
Linux System Programming: File handling, signals (SIGINT), process management.
Docker: Containerization, volume mounting.
STL Containers: std::queue, std::unordered_map.

✅ Challenges & Solutions
Race Condition Between Threads: Fixed by ensuring producer thread completes before consumer starts in beginner mode.
Real-Time File Monitoring in WSL: WSL file buffering required batch processing for predictable output.
Error Handling: Proper messages and exit codes implemented for invalid logs or missing files.

🎯 Conclusion:
This project demonstrates:

Strong C++ programming fundamentals
Linux environment expertise
Thread-safe multi-threaded design
Docker containerization skills
It is HR-friendly, easy to read, and clearly showcases problem-solving and engineering skills.

💡 Future Improvements

Upgrade to full real-time tailing mode using std::filesystem and signals.
Implement TCP socket server to stream log summaries.
Integrate CI/CD pipeline for auto-build and deployment.
