#include "nrpch.h"
#include "Neuron/Core/Input.h"
#include "Neuron/Core/Application.h"

#include <GLFW/glfw3.h>

namespace Neuron {
    bool Input::IsKeyPressed(const KeyCode key) {
        auto *window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
        auto state = glfwGetKey(window, static_cast<int32_t>(key));
        return state == GLFW_PRESS;
    }

    bool Input::IsMouseButtonPressed(const MouseCode button) {
        auto *window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
        auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));
        return state == GLFW_PRESS;
    }

    glm::vec2 Input::GetMousePosition() {
        auto *window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);

        return {(float) xPos, (float) yPos};
    }

    float Input::GetMouseX() {
        return GetMousePosition().x;
    }

    float Input::GetMouseY() {
        return GetMousePosition().y;
    }
}