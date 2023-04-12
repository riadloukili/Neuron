#pragma once

#include "Neuron/Core/Base.h"
#include "Neuron/Core/Application.h"


#if defined(NR_PLATFORM_LINUX) || defined(NR_PLATFORM_MACOS)

int main(int argc, char **argv) {
    Neuron::Log::Init();
    auto app = Neuron::CreateApplication({argc, argv});
    app->Run();
    delete app;
}

#elif defined(NR_PLATFORM_WINDOWS)

int main(int argc, char **argv) {
    Neuron::Log::Init();
    auto app = Neuron::CreateApplication({argc, argv});
    app->Run();
    delete app;
}

#endif