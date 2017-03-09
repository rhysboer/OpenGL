#pragma once
#include <stdlib.h>
#include <time.h>
#include "gl_core_4_4.h"
#include "GLFW\glfw3.h"

class BaseApplication {
public:
	BaseApplication(int width, int height, const char* name);
	~BaseApplication();

	virtual const bool Update() = 0;
	virtual void Draw() = 0;

	virtual const bool Startup() = 0;
	virtual void Shutdown() = 0;

	GLFWwindow* GetWindow() const;

protected:

	GLFWwindow* window;
};

