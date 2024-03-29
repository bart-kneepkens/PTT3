#ifndef MODULE_MODULEHANDLER_HPP
#define MODULE_MODULEHANDLER_HPP

#include <netinet/in.h>
#include <iostream>
#include <pthread.h>

#include "../SocketUtils/SocketUtils.hpp"
#include "ModuleData.hpp"
#include "../Logger/Logger.hpp"

/**
 * Responsible for registering and storing modules. Not thread-safe.
 */
class ModuleHandler {
private:
    /** The socket file descriptor to which this handler listens. */
    int sockfd;

    /** The port on which this handler is listening. */
    const int port;

    /** Mutex indicating whether or not this handler is listening (it is listening if this mutex is locked). */
    pthread_mutex_t isListening;

    /** All registered modules. */
    std::vector<ModuleData> modules;

    /** Mutex used for making the modules vector thread-safe. */
    //pthread_mutex_t modulesMutex;

    /** Thread that listens to incoming module registrations until cancelled. */
    pthread_t listeningThread;

    /**
     * Listens to incoming module registrations until cancelled.
     * @param threadArgs
     * @return
     */
    static void *ListenToIncomingModules(void *threadArgs);
public:
    /**
     * Constructor.
     * @param port The port to listen to.
     * @return
     */
    ModuleHandler(const int port);

    /**
     * Destructor. Calls StopListening.
     */
    ~ModuleHandler();

    /**
     * Returns a copy of all modules.
     * @return
     */
    std::vector<ModuleData> GetModules();

    /**
     * Starts listening to incoming module registrations.
     * If called twice without a call to StopListening inbetween, the second call is ignored.
     * @return True if this has begun listening, false if it was already listening.
     */
    bool StartListening();

    /**
     * Stops listening to incoming module registrations.
     * If this is not already listening, then the call is ignored.
     * @return True if this was listening before this was called, false otherwise.
     */
    bool StopListening();

    /**
     * Gets the module with the supplied socket id.
     * @param socketId
     * @return
     */
    ModuleData GetModule(int socketId);

    /**
     * Closes and removes the module with the supplied socket id from this handler.
     * @param socketId
     */
    void CloseAndRemoveModule(int socketId);
};

#endif //MODULE_MODULEHANDLER_HPP
