FROM ubuntu:22.04

# Install compiler
RUN apt update && apt install -y g++

# Create app directory
WORKDIR /app

# Copy project files
COPY . .

# Compile the C++ program
RUN g++ -std=c++17 src/main.cpp -o log_processor -pthread

# Run the application
CMD ["./log_processor"]
