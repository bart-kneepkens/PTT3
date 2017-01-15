#ifndef MODULESSERVER_MODULECHAIN_HPP
#define MODULESSERVER_MODULECHAIN_HPP

#include <string>
#include <vector>
#include <stdexcept>

#include "ModuleData.hpp"
#include "../Logger/Logger.hpp"

/**
 * Responsible for holding a created chain of modules and calling them in consecutive order.
 */
class ModuleChain {
private:
    /** This chain's modules. */
    std::vector<ModuleData> modules;
public:
    /**
     * Constructor.
     * @return
     */
    ModuleChain();

    /**
     * Returns a string representation of this chain.
     * @return
     */
    std::string ToString() const;

    /**
     * Appends the supplied module to this chain.
     * @param moduleData
     * @throws std::invalid_argument if the supplied module cannot be appended.
     */
    void AppendModule(ModuleData& moduleData);

    /**
     * Runs this module chain, causing it to call all modules in consecutive order.
     */
    void Run() const;
};

#endif //MODULESSERVER_MODULECHAIN_HPP
