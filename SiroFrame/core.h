#ifndef CORE_H_
#define CORE_H_

class SiroCore {

public:
	SiroCore();

	void StartupConsole(const char* name = "SiroFrame");

	int ShutdownConsole();

	void RunGame(class Game* game);

	void RunGame(void (*setup)(), void (*loop)());

private:
	class SiroRenderer* _renderer;
	class SiroInput* _input;
	class Game* _cartridge;
	struct GLFWwindow* _window;
	double _starttime;
	void(*_keysetup)();
};

#endif
