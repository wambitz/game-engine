//IPlugin.h
#pragma once

namespace Engine
{

class IPlugin
{
public:
    virtual ~IPlugin() = default;
    virtual void onLoad() = 0;
    virtual void onUnload() = 0;
    virtual void execute() = 0;
};

} // namespace Engine
