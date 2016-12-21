#include <iostream>
#include "../Common/LogBuffer.h"
#include <sys/mman.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdio.h>
#include <fcntl.h>

const char* SHM_NAME = "LogBuffer";

struct LogBuffer* buff;

int shm_fd;

int main(){
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
    
    while(true){
		
	}
}
