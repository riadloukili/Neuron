#include "nrpch.h"
#include "Neuron/Utils/PlatformUtils.h"

#include <GLFW/glfw3.h>

namespace Neuron {

    float Time::GetTime() {
        return static_cast<float>(glfwGetTime());
    }

}