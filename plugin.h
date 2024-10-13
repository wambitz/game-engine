// plugin.h
#pragma once

// extern "C" tells the C++ compiler to use C linkage for the specified function(s),
// meaning the names will not be mangled and will be treated like regular C functions.
// This is important in scenarios where you need to interact with C libraries,
// dynamically load functions by their unmangled name,
// or expose functions from C++ libraries to C or C-compatible systems.

#include "IPlugin.h"

namespace PluginNamespace  {

class Plugin : public Engine::IPlugin {
public:
    Plugin() = default;
    ~Plugin() override = default;

    void onLoad() override;
    void onUnload() override;
    void execute() override;
};

// Factory function for creating a plugin instance
extern "C" {
    Engine::IPlugin* createPlugin();
}

} // namespace PluginNamespace 
