#include "BaseApplication.h"
#include <stdlib.h>
#include <time.h>

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
