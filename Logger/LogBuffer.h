#ifndef LOGGER_LOGBUFFER_HPP
#define LOGGER_LOGBUFFER_HPP

#include "LogMessage.h"
#include <semaphore.h>

struct LogBuffer {
	LogMessage messages[10];
	sem_t filled;
	sem_t empty;
};

#endif // LOGGER_LOGBUFFER_HPP
