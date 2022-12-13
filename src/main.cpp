#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

int g_windowSizeX = 640; // ������ ����
int g_windowSizeY = 480; // ������ ����

// ��������� ��������� ����
void glfwWindowSizeCallback(GLFWwindow* pWindow, int width, int height) {
    g_windowSizeX = width;
    g_windowSizeY = height;
    // ������������� ������� ���������, ������� ��������� ���������� �������� ������ ���� � ������� �������
    glViewport(0, 0, g_windowSizeX, g_windowSizeY); 
}

// ��������� ������� ������
void glfwKeyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mode) {
    // ��������� ������� ������� ESCAPE
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        // ��������� ����� ��� �������� ����
        glfwSetWindowShouldClose(pWindow, GL_TRUE);
    }
}

int main(void)
{
    // �������� ������� ������������� glfw, ��������� �����������������
    if (!glfwInit()) {
        std::cout << "Can't load GLFW" << std::endl;
        return -1;
    }

    // ��������� ������������ ������ OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    // ��������� ����� ����������� �������, � ������ ������ ��������� ������ ������� �������
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // �������� ����, �������� ���� � ��� �������� OpenGL
    GLFWwindow* pWindow = glfwCreateWindow(g_windowSizeX, g_windowSizeY, "Sapper", nullptr, nullptr);
    if (!pWindow)
    {
        std::cout << "glfwCreateWindow failed! Failed to create a window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // ������������ ������� ��������� ��������� ����, ������� ��������� �� ���� � ���� �������
    glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallback);
    // ������������ ������� ��������� ������� ������
    glfwSetKeyCallback(pWindow, glfwKeyCallback);

    // ��������� �������� ���� �������
    glfwMakeContextCurrent(pWindow);

    // �������� ������� ������������� glad, ��������� �����������������
    if (!gladLoadGL()) {
        std::cout << "Can't load GLAD" << std::endl;
        return -1;
    }

    // ���������� ���������� �� OpenGL
    std::cout << "Render: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    glClearColor(0,1,0,1);

    // ������� ������ ���������
    // ����������� ���� ������������ �� ������� ����
    while (!glfwWindowShouldClose(pWindow))
    {
        // ������, ������� ������ �� ����� 
        glClear(GL_COLOR_BUFFER_BIT);

        // ������ ������� �������� � ������ ������ (������ ������ ������������ � ����������, � �������� ������������ �� ��������)
        glfwSwapBuffers(pWindow);

        // ��������� ������� / ������� ������, ��������� ������� �������, �������� ���� � �.�.
        glfwPollEvents();
    }

    // ��������� ������ ��������� � ����������� �������
    glfwTerminate();
    return 0;
}