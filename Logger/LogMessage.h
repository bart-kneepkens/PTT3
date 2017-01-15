#ifndef LOGGER_LOGMESSAGE_HPP
#define LOGGER_LOGMESSAGE_HPP

#include <time.h>

struct LogMessage {
	char text[256];
	time_t timestamp;
};

#endif // LOGGER_LOGMESSAGE_HPP
