#ifndef PTT3_MODULEDATA_HPP
#define PTT3_MODULEDATA_HPP

#include <string>
#include <stdexcept>

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
                PLOTTER
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
    const ModuleType::ModuleType type;
    const ModuleSubType::ModuleSubType subType;
    const int socketId;
public:
    ModuleData(ModuleType::ModuleType type, ModuleSubType::ModuleSubType subType, int socketId);

    ~ModuleData();

    ModuleType::ModuleType GetType() const;

    ModuleSubType::ModuleSubType GetSubType() const;

    int GetSocketId() const;
};

#endif //PTT3_MODULEDATA_HPP
