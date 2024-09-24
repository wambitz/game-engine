
#include "engine_core.h"

int main()
{
    Engine::EngineCore engine;

    // Initialize the engine
    engine.initialize();

    // Run the game loop
    engine.run();

    // Shutdown the engine
    engine.shutdown();

    return 0;
}