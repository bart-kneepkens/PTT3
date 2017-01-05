#include <iostream>
#include "../Common/LogBuffer.h"
#include <sys/mman.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdio.h>
#include <fcntl.h>
#include <fstream>


const char* SHM_NAME = "LogBuffer";

struct LogBuffer* buff;

int shm_fd;

LogMessage takeLastFromBuffer(){
	LogMessage last = buff->messages[9];

	for(int i = 1; i < 9; i++){
		buff->messages[i -1 ] = buff->messages[i];
	}
	
	return last;
}

int main(){
	munmap(buff, sizeof(LogBuffer));
	
	// Get shared memory file descriptor.
    if ((shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666)) == -1){
        perror("cannot open");
        return -1;
    }
    
    // Set the shared memory size to the size of LogBuffer struct.
    if (ftruncate(shm_fd, sizeof(LogBuffer)) != 0){
        perror("cannot set size");
        return -1;
    }
    
    // Map shared memory in address space.
    if ((buff = (struct LogBuffer *) mmap(0, sizeof(LogBuffer), PROT_WRITE, MAP_SHARED, shm_fd, 0)) == MAP_FAILED){
        perror("cannot mmap");
        return -1;
    }
    
    // Lock the shared memory.
    if (mlock(buff, sizeof(LogBuffer)) != 0){
        perror("cannot mlock");
        return -1;
    }
    
    // Shared memory is ready for use.
    printf("Shared Memory successfully opened.\n");
    
    // Initialize semaphore 'filled' with value 0.
	if(sem_init(&(buff->filled), 1, 0) != 0){
		perror("Can not init semaphore 'filled'");
		return -1;
	}

	// Initialize semaphore 'empty' with value 10.
	if(sem_init(&(buff->empty), 1, 10) != 0){
		perror("Can not init semaphore 'empty'");
		return -1;
	}
	
	// Open LogFile
	std::ofstream logFile;
	logFile.open("MazeSolverLogs", std::ofstream::out | std::ofstream::app);
	char dateFormatted[18];
	struct tm *tm;
  
    // Wait for Logger class to make isRady true before entering
    // Else the semaphores are not initialised resulting in a deadlock.
    while(true){
		sem_wait(&(buff->filled));
		LogMessage msg = takeLastFromBuffer();
		sem_post(&(buff->empty));
		tm = localtime(&(msg.timestamp));
		strftime(dateFormatted, sizeof(dateFormatted), "%D,%T", tm);
		logFile << dateFormatted << " :: " << msg.text << std::endl;
		std::cout << dateFormatted << " :: " << msg.text << std::endl;
	}
}
