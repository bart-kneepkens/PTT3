#ifndef PTT3_MODULEDATA_HPP
#define PTT3_MODULEDATA_HPP

#include <string>
#include <stdexcept>

#include "../SocketUtils/SocketUtils.hpp"
#include "../maze_parser/MazeMessage.hpp"
#include "../maze_parser/MazeParser.hpp"
#include "../Logger/Logger.hpp"

namespace ModuleType {
    /** The main types of a connected module. */
    enum ModuleType {
        /** Server expects data from the module, but sends nothing/empty message. */
                IN,
        /** Server expects data from the module and also sends data. */
                INOUT,
        /** Server expects nothing/empty message from the module, but sends data. */
                OUT
    };

    /**
     * Parses a string to a ModuleType.
     * @throws std::invalid_argument if string could not be parsed.
     * @param str
     * @return
     */
    ModuleType FromString(std::string str);

    /**
     * Parses a ModuleType to a string.
     * @param moduleType
     * @return
     */
    std::string ToString(ModuleType moduleType);
}

namespace ModuleSubType {
    /** The specific types of a connected module. */
    enum ModuleSubType {
        /** Main type: IN. Scans a maze from a piece of paper. */
                SCANNER,
        /** Main type: INOUT. Solves a maze. */
                SOLVER,
        /** Main type: OUT. Prints a maze. */
                PLOTTER,
	/** Main type: OUT. Prints a maze in the terminal. */
		SIMPLEMAZEPRINTER
    };

    /**
    * Parses a string to a ModuleSubType.
    * @throws std::invalid_argument if string could not be parsed.
    * @param str
    * @return
    */
    ModuleSubType FromString(std::string str);

    /**
    * Parses a ModuleSubType to a string.
    * @param moduleSubType
    * @return
    */
    std::string ToString(ModuleSubType moduleSubType);
}

/** Holds data of a single Module Client that registered itself to the server. */
class ModuleData {
private:
    /** This module's main type (in, inout, or out). */
    ModuleType::ModuleType type;

    /** This module's subtype (scanner, solver, parser, etc.). */
    ModuleSubType::ModuleSubType subType;

    /** This module's socket id. */
    int socketId;
public:
    /**
     * Constructor.
     * @param type This module's main type (in, inout, or out).
     * @param subType This module's subtype (scanner, solver, parser, etc.).
     * @param socketId  This module's socket id.
     * @return
     */
    ModuleData(ModuleType::ModuleType type, ModuleSubType::ModuleSubType subType, int socketId);

    /**
     * Destructor.
     */
    ~ModuleData();

    /**
     * Gets this module's main type.
     * @return This module's main type.
     */
    ModuleType::ModuleType GetType() const;

    /**
     * Gets this module's subtype.
     * @return This module's subtype.
     */
    ModuleSubType::ModuleSubType GetSubType() const;

    /**
     * Gets this module's socket id.
     * @return This module's socket id.
     */
    int GetSocketId() const;

    /**
     * Makes a call via the socket to the actual remote module, sending the supplied MazeMessage and returning a
     * MazeMessage replied by the remote module.
     * @param msg The MazeMessage to send to the remote module, or NULL. After the call, contains the replied MazeMessage.
     * @throws std::logical_error if sending or receiving failed.
     */
    void Run(maze_parser::MazeMessage *&msg) const;
};

#endif //PTT3_MODULEDATA_HPP
