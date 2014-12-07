#include <iostream>

using namespace std;

#include "GLFW/glfw3.h"

int main() {
    cout << "Hello, World!" << endl;
    if (!glfwInit())
        return 1;
    return 0;
}