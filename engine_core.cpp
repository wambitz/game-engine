#include "engine_core.h"

#include <dlfcn.h> // For dynamic loading
#include <iostream>

using namespace Engine;

// Declaration of the dynamically linked render function
extern "C" void render(); // Declaration of the render function from librender.so

void EngineCore::initialize()
{
    // TBD
}

void EngineCore::run()
{
    // 1. Call the dynamically linked library (librender.so)
    std::cout << "Calling the dynamically linked library (Render Engine):" << std::endl;
    render(); // Call the function from librender.so

    // 2. Dynamically load the plugin (libplugin.so) at runtime
    std::cout << "\nLoading the plugin dynamically at runtime:" << std::endl;
    void* handle = dlopen("./libplugin.so", RTLD_LAZY); // Load the plugin
    if (!handle)
    {
        std::cerr << "Cannot open library: " << dlerror() << std::endl;
        // return 1;
    }

    // Reset errors
    dlerror();

    // Load the symbol (helloPlugin function)
    typedef void (*hello_t)();
    hello_t helloPlugin = (hello_t)dlsym(handle, "helloPlugin");

    const char* dlsym_error = dlerror();
    if (dlsym_error)
    {
        std::cerr << "Cannot load symbol 'helloPlugin': " << dlsym_error << std::endl;
        dlclose(handle);
        // return 1;
    }

    // Call the plugin function
    helloPlugin();

    // Close the library
    dlclose(handle);
}

void EngineCore::shutdown()
{
    // TBD
}