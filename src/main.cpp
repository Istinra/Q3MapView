#include "GLFW/glfw3.h"

int main() {

    if (!glfwInit())
    {
        return 1;
    }

    GLFWwindow* window = glfwCreateWindow(640, 480, "Q3MapView", nullptr, nullptr);

    glfwTerminate();

    return 1;
}