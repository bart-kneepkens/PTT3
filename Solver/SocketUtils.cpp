#include "SocketUtils.hpp"

int sendMsg(int socket, char buffer[]) {
    const int n = write(socket, buffer, strlen(buffer));
    if (n < 0) {
        perror("Error while writing to socket!");
    }
    return n;
}

int receiveMsg(int socket, char buffer[], unsigned int bufferSize) {
    bzero(buffer, bufferSize);
    const int n = read(socket, buffer, bufferSize - 1);
    if (n < 0) {
        perror("Error while reading from socket!");
    }
    return n;
}
