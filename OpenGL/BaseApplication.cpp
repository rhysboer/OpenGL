#include "BaseApplication.h"

BaseApplication::BaseApplication(int width, int height, const char * name) {
	if (glfwInit() == false)
		return;

	this->window = glfwCreateWindow(width, height, name, nullptr, nullptr);

	srand(time(NULL));
}

BaseApplication::~BaseApplication() {
	glfwDestroyWindow(window);
	glfwTerminate();
}

GLFWwindow * BaseApplication::GetWindow() const {
	return window;
}
