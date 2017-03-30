#pragma once
#include "gl_core_4_4.h"
#include "GLFW\glfw3.h"
#include "GLM\glm.hpp"

using glm::vec2;

class InputManager {
public:
	~InputManager();

	static void MousePosition(double& x, double& y);
	static vec2 MousePosition();

	static bool IsKeyDown(const int key);
	static bool IsMouseButtonDown(const int key);
	//static bool WasKeyPressed(const int key);
	//static bool WasMouseButtonPressed(const int key);

	static void Init(GLFWwindow* window);
	static void PollEvents();

private:
	InputManager(GLFWwindow* window);

	static InputManager* m_instance;
	static GLFWwindow* m_window;
};

