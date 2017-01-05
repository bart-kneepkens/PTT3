#include "../Common/LogBuffer.h"
#include <iostream>
#include <sys/mman.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>

class Logger {
	public:
        static Logger& getInstance(){
            static Logger instance; // Guaranteed to be destroyed.      
            return instance; // Instantiated on first use.
        }
        
        void logMessage(std::string message){
			LogMessage msg;
			
			strcpy(msg.text, message.c_str());
			time(&msg.timestamp);
			
			sem_wait(&(buff->empty));
			
			addToBuffer(msg);
			
			sem_post(&(buff->filled));
			
			std::cout << "Logged Message: " << msg.text << ":" << msg.timestamp << std::endl;
		}
    private:    
        char* SHM_NAME;
		
		struct LogBuffer* buff;

		int shm_fd;
		
        Logger() {
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
		                    
        Logger(Logger const&);              // Don't Implement
        void operator=(Logger const&); 		// Don't implement

		void addToBuffer(LogMessage msg){
			for (int i = 0; i < 9; i++){
				buff->messages[i] = buff->messages[i+1];
			}
			buff->messages[9] = msg;
		}
};




