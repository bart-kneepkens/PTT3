/**
 * Holds several constants and utility functions that are used by both ModuleClient and ModuleServer.
 */

#ifndef PTT3_SOCKETUTILS_HPP
#define PTT3_SOCKETUTILS_HPP

#include <string>
#include <unistd.h>
#include <cstring>
#include <vector>
#include <sstream>
#include <stdint.h>
#include <stdio.h>

// Constant values and settings.
const uint16_t MAZE_MSG_BUFFER_SIZE = 2048;             // Buffer size for Maze Messages.
const uint16_t ACK_BUFFER_SIZE = 4;                     // Buffer size for ACK messages.
const char DELIMITER = '^';                             // Delimiter for incoming messages.
const std::string SCANNER_STRING = "in:scanner";        // String that corresponds to MazeScanner.
const std::string SOLVER_STRING = "inout:solver";       // String that corresponds to MazeSolver.
const std::string PLOTTER_STRING = "out:plotter";       // String that corresponds to MazePlotter (to be implemented).
const std::string SIMPLEMAZEPRINTER_STRING = "out:simplemazeprinter"; // String that corresponds to SimpleMazePrinter.
const char ACK_MSG[ACK_BUFFER_SIZE] = {'A', 'C', 'K'};  // Message that is sent as acknowledgement.

/**
 * Sends the specified message in 'buffer' through the specified socket. The socket should already be open before
 * this function is called.
 *
 * @param socket
 * @param buffer
 * @return
 */
int sendMsg(int socket, char buffer[]);

/**
 * Receives a message of the specified size through the specified socket and places it in 'buffer'.
 * The socket should already be open before this function is called.
 *
 * @param socket
 * @param buffer
 * @param bufferSize
 * @return
 */
int receiveMsg(int socket, char buffer[], unsigned int bufferSize);

/**
 * Splits the supplied string on the supplied delimiter.
 * @param str
 * @param delimiter
 * @return
 */
std::vector<std::string> splitString(std::string str, char delimiter);

#endif //PTT3_SOCKETUTILS_HPP
