#include "BaseApplication.h"

BaseApplication::BaseApplication(int width, int height, const char * name) {
	if (glfwInit() == false)
		return;

	srand(time(NULL));

	this->window = glfwCreateWindow(width, height, name, nullptr, nullptr);
}

BaseApplication::~BaseApplication() {
	glfwDestroyWindow(window);
	glfwTerminate();
}

GLFWwindow * BaseApplication::GetWindow() const {
	return window;
}
