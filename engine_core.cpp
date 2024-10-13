// engine_core.h
#include "IPlugin.h"  // Include full definition of IPlugin
#include "engine_core.h"
#include "render.h"

#include <dlfcn.h> // For dynamic loading
#include <iostream>

namespace Engine {

typedef IPlugin* (*CreatePluginFunc)();

void EngineCore::initialize() {
    // Initialize engine systems
    std::cout << "Engine initialized." << std::endl;
}

void EngineCore::run() {

    // 1. Call the dynamically linked library (librender.so)
    std::cout << "Calling the dynamically linked library (Render Engine):" << std::endl;
    render();  // Direct call to render function

    // Load the plugin
    loadPlugin("./libplugin.so");

    if (plugin_) {
        // Call the plugin's onLoad method
        plugin_->onLoad();

        // Main loop (simplified)
        std::cout << "Engine running..." << std::endl;
        plugin_->execute();

        // Call the plugin's onUnload method
        plugin_->onUnload();
    }
}

void EngineCore::shutdown() {
    // Clean up and close the plugin
    if (plugin_) {
        plugin_.reset();
    }
    if (pluginHandle_) {
        dlclose(pluginHandle_);
        pluginHandle_ = nullptr;
    }
    std::cout << "Engine shutdown." << std::endl;
}

void EngineCore::loadPlugin(const std::string& pluginPath) {
    pluginHandle_ = dlopen(pluginPath.c_str(), RTLD_LAZY);
    if (!pluginHandle_) {
        std::cerr << "Cannot open plugin library: " << dlerror() << std::endl;
        return;
    }

    // Reset errors
    dlerror();

    // Load the factory function
    CreatePluginFunc createPlugin = (CreatePluginFunc)dlsym(pluginHandle_, "createPlugin");
    const char* dlsymError = dlerror();
    if (dlsymError) {
        std::cerr << "Cannot load symbol 'createPlugin': " << dlsymError << std::endl;
        dlclose(pluginHandle_);
        pluginHandle_ = nullptr;
        return;
    }

    // Create an instance of the plugin
    plugin_.reset(createPlugin());
}

} // namespace Engine
