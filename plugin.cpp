// libplugin.cpp
#include "plugin.h"
#include <iostream>

// Technically, extern "C" is not required in the source file
// if you’ve already declared the function as extern "C" in the header file.
// The source file’s implementation will use the linkage specified in the header.
// However, it’s a good practice to use extern "C" in both the header and
// the source file to make the linkage explicit.
// This ensures consistency and clarity, especially in larger projects where
// someone might look at the source file directly without referencing the header.

#include "plugin.h"
#include <iostream>

namespace PluginNamespace
{

void Plugin::onLoad() { std::cout << "Plugin loaded." << std::endl; }

void Plugin::onUnload() { std::cout << "Plugin unloaded." << std::endl; }

void Plugin::execute() { std::cout << "Plugin executing." << std::endl; }

// Factory function implementation
extern "C"
{

    Engine::IPlugin* createPlugin() { return new Plugin(); }

} // extern "C"

} // namespace PluginNamespace
