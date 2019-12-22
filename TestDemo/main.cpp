#include "../MixEngine.h"
#include <SDL2/SDL_main.h>

#include "TestDemo.h"

extern "C" int main(int argc, char** argv) {
    Mix::MixEngine::Initialize("Mix", argc, argv);
    return Mix::MixEngine::Instance().execute(std::make_shared<TestDemo>());
}
