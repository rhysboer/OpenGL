#include "BaseApplication.h"

BaseApplication::BaseApplication(int width, int height, const char * name) {
	if(glfwInit() == false)
		return;

	this->window = glfwCreateWindow(width, height, name, nullptr, nullptr);
}

BaseApplication::~BaseApplication() {
	glfwDestroyWindow(window);
	glfwTerminate();
}
