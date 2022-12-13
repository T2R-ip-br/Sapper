#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

int g_windowSizeX = 640; // Ширина окна
int g_windowSizeY = 480; // Высота окна

// Обработка изменения окна
void glfwWindowSizeCallback(GLFWwindow* pWindow, int width, int height) {
    g_windowSizeX = width;
    g_windowSizeY = height;
    // Устанавливает область отрисовки, сначала указываем координаты верхнего левого угла и нижнего правого
    glViewport(0, 0, g_windowSizeX, g_windowSizeY); 
}

// Обработка нажатия клавиш
void glfwKeyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mode) {
    // Обработка нажатия клавиши ESCAPE
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        // Установка флага для закрытия окна
        glfwSetWindowShouldClose(pWindow, GL_TRUE);
    }
}

int main(void)
{
    // Вызываем функцию инициализации glfw, проверяем работоспособность
    if (!glfwInit()) {
        std::cout << "Can't load GLFW" << std::endl;
        return -1;
    }

    // Указываем используемую версию OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    // Указываем выбор необходимых функций, в данном случае указываем только базовые функции
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Создание окна, настроек окна и его контекст OpenGL
    GLFWwindow* pWindow = glfwCreateWindow(g_windowSizeX, g_windowSizeY, "Sapper", nullptr, nullptr);
    if (!pWindow)
    {
        std::cout << "glfwCreateWindow failed! Failed to create a window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Регистрируем функцию обработки изменения окна, передаём указатель на окно и саму функцию
    glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallback);
    // Регистрируем функцию обработки нажатия клавиш
    glfwSetKeyCallback(pWindow, glfwKeyCallback);

    // Указываем контекст окна текущим
    glfwMakeContextCurrent(pWindow);

    // Вызываем функцию инициализации glad, проверяем работоспособность
    if (!gladLoadGL()) {
        std::cout << "Can't load GLAD" << std::endl;
        return -1;
    }

    // Отображаем информацию об OpenGL
    std::cout << "Render: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    glClearColor(0,1,0,1);

    // Главный рендер отрисовки
    // Выполняется пока пользователь не закроет окно
    while (!glfwWindowShouldClose(pWindow))
    {
        // Рендер, очистка буфера от цвета 
        glClear(GL_COLOR_BUFFER_BIT);

        // Меняет местами передний и задний буффер (задний буффер генерируется в видеокарте, а передний отображается на мониторе)
        glfwSwapBuffers(pWindow);

        // Обработка событий / нажатие клавиш, изменение позиции курсора, закрытие окна и т.п.
        glfwPollEvents();
    }

    // Завершаем работу программы и освобождаем ресурсы
    glfwTerminate();
    return 0;
}