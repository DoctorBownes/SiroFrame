#include <SiroFrame/core.h>
#include <SiroFrame/game.h>
#include <SiroFrame/input.h>
#include <SiroFrame/Internal/renderer.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

int _framecounter = 0;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport((width - 1024) / 2, (height - 768) / 2, 1024, 768);
};

SiroCore::SiroCore() {
    _window = nullptr;
    _renderer = nullptr;
    _cartridge = nullptr;
    _input = nullptr;
    _keysetup = nullptr;
    _starttime = 0.0;
}

void SiroCore::StartupConsole(const char* name) {
    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    _window = glfwCreateWindow(1024, 768, name, NULL, NULL);

    if (_window == NULL) {
        fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
        glfwTerminate();
        return;
    }
    glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);
    glfwMakeContextCurrent(_window);
    //glfwSwapInterval(0);

    if (!gladLoadGL()) {
        fprintf(stderr, "Failed to initialize GLAD.\n");
        glfwTerminate();
    }

    _renderer = _renderer->GetRenderer();
    _renderer->SetupRenderer();
    _input = _input->PlugInKeyboard();
    _input->_window = _window;
}

int SiroCore::ShutdownConsole() {
	return glfwWindowShouldClose(_window);
}

void SiroCore::RunGame(Game* game) {
    if (glfwGetTime() - _starttime > 0.0162f) {//60 FPS CAP
        glClearColor(_renderer->rgba_palettebuffer[0] * 0.00392f, _renderer->rgba_palettebuffer[1] * 0.00392f, _renderer->rgba_palettebuffer[2] * 0.00392f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

       _framecounter++;

      _input->_presscalled = 0;
      _input->_relescalled = 0;

       if (_cartridge != game) {

           _cartridge = game;

           _cartridge->setup();
       }

       _cartridge->loop();

       _renderer->UpdateGameScreen();

       _renderer->DrawGameScreen();

       glfwSwapBuffers(_window);
       glfwPollEvents();

       _starttime = glfwGetTime();
    }
}

void SiroCore::RunGame(void(*setup)(), void(*loop)()) {
    if (glfwGetTime() - _starttime > 0.0162f) {//60 FPS CAP
        glClearColor(_renderer->rgba_palettebuffer[0] * 0.00392f, _renderer->rgba_palettebuffer[1] * 0.00392f, _renderer->rgba_palettebuffer[2] * 0.00392f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        _framecounter++;

        _input->_presscalled = 0;
        _input->_relescalled = 0;

        if (_keysetup != setup) {

            _keysetup = setup;

            _keysetup();
        }

        loop();

        _renderer->UpdateGameScreen();

        _renderer->DrawGameScreen();

        glfwSwapBuffers(_window);
        glfwPollEvents();

        _starttime = glfwGetTime();
    }
}
