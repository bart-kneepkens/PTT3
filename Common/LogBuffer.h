#include "LogMessage.h"
#include <semaphore.h>

struct LogBuffer {
	LogMessage messages[10];
	sem_t filled;
	sem_t empty;
	bool isReady;
};
