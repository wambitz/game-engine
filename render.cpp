// librender.cpp
#include <iostream>

extern "C" void render() { std::cout << "Rendering from the dynamically linked library (librender.so)" << std::endl; }
