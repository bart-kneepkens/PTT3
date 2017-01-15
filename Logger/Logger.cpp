#include "Logger.hpp"

Logger::Logger() {
    SHM_NAME = "LogBuffer";

    // Get shared memory file descriptor.
    if ((shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666)) == -1){
        perror("cannot open");
    }

    // Set the shared memory size to the size of LogBuffer struct.
    if (ftruncate(shm_fd, sizeof(LogBuffer)) != 0){
        perror("cannot set size");
    }

    // Map shared memory in address space.
    if ((buff = (struct LogBuffer *) mmap(0, sizeof(LogBuffer), PROT_WRITE, MAP_SHARED, shm_fd, 0)) == MAP_FAILED){
        perror("cannot mmap");
    }

    // Lock the shared memory.
    if (mlock(buff, sizeof(LogBuffer)) != 0){
        perror("cannot mlock");
    }

    // Shared memory is ready for use.
    printf("LOGGER: Shared Memory successfully opened.\n");
}

void Logger::addToBuffer(LogMessage msg) {
    // Firstly push every struct in the buffer one place foward.
    for (int i = 0; i < 9; i++){
        buff->messages[i] = buff->messages[i+1];
    }

    // Place the struct at the back of the buffer.
    buff->messages[9] = msg;
}

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

void Logger::logMessage(std::string message) {
    LogMessage msg;

    strcpy(msg.text, message.c_str());  // Copy the string into the struct.
    time(&msg.timestamp);               // Put a timestamp into the struct.

    sem_wait(&(buff->empty));           // Wait and lower the empty semaphore.

    addToBuffer(msg);

    sem_post(&(buff->filled));          // Up the filled semaphore.

    std::cout << "Logged Message: " << msg.text << ":" << msg.timestamp << std::endl;
}




