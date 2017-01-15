#ifndef LOGGER_LOGGERCENTRAL_HPP
#define LOGGER_LOGGERCENTRAL_HPP

#include <iostream>
#include "LogBuffer.h"
#include <sys/mman.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdio.h>
#include <fcntl.h>
#include <fstream>

/*
 LoggerCentral is the class that takes logged messages from shared memory and writes them to a file.
 */
class LoggerCentral {
public:
    LoggerCentral();

    void run();

private:
    char* SHM_NAME;

    struct LogBuffer* buff;

    int shm_fd;

    // Takes the last LogMessage from the shared memory buffer. (LIFO)
    LogMessage takeLastFromBuffer();
};

#endif //LOGGER_LOGGERCENTRAL_HPP
