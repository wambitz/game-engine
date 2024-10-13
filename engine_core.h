// engine_core.h
#pragma once

#include "IPlugin.h"
#include <memory>

namespace Engine
{

class EngineCore
{
public:
    void initialize();
    void run();
    void shutdown();

private:
    void loadPlugin(const std::string& pluginPath);

    // Use a smart pointer for automatic memory management
    std::unique_ptr<IPlugin> plugin_;
    void* pluginHandle_ = nullptr;
};

} // namespace Engine
