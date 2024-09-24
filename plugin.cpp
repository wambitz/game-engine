// libplugin.cpp
#include <iostream>

extern "C" void helloPlugin() { std::cout << "Hello from the dynamically loaded plugin (libplugin.so)" << std::endl; }
