#ifndef LOGGER_LOGGER_HPP
#define LOGGER_LOGGER_HPP

#include "LogBuffer.h"
#include <iostream>
#include <sys/mman.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>

/*
 Logger is the class that has the responsibility of handling a string, and transferring it to the LoggerCentral.
 It is a singleton because one and only one instance should ever exist.
 */
class Logger {
public:
    // This function makes this class a singleton.
    static Logger& getInstance();

    // This function takes a string and creates a LogMessage struct, after which it adds it to shared memory.
    void logMessage(std::string message);
private:
    char* SHM_NAME;

    struct LogBuffer* buff;

    int shm_fd;

    Logger();

    Logger(Logger const&);              // Don't Implement
    void operator=(Logger const&); 		// Don't implement

    // Adds a LogMessage struct to the shared memory. (LIFO)
    void addToBuffer(LogMessage msg);
};

#endif //LOGGER_LOGGER_HPP
