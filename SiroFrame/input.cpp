#include <SiroFrame/input.h>
#include <GLFW/glfw3.h>

SiroInput* SiroInput::_instance = 0;

SiroInput::SiroInput() {
	_window = nullptr;
}

SiroInput::~SiroInput() {
	//delete _instance;
}

bool SiroInput::KeyPressed(KeyCode key) {
	unsigned char keystatus = glfwGetKey(_window, (int)key);
	if (keystatus && _presscalled) {
		return 1;
	}
	if (keystatus && !keypressed[key]) {
		keypressed[key] = true;
		_presscalled = 1;
		return 1;
	}
	else if (!keystatus) {
		keypressed[key] = false;
	}
	return 0;
}

bool SiroInput::KeyReleased(KeyCode key) {
	unsigned char keystatus = glfwGetKey(_window, (int)key);
	if (!keystatus && _relescalled) {
		return 1;
	}
	if (!keystatus && keyreleased[key]) {
		keyreleased[key] = false;
		_relescalled = 1;
		return 1;
	}
	if (keystatus) {
		keyreleased[key] = true;
	}
	return 0;
}

bool SiroInput::KeyDown(KeyCode key) {
	return glfwGetKey(_window, (int)key);
}
