#include "InputManager.h"

InputManager* InputManager::m_instance = nullptr;
GLFWwindow* InputManager::m_window = nullptr;

InputManager::~InputManager() {
}

void InputManager::MousePosition(double & x, double & y) {
	if(m_window != nullptr) {
		glfwGetCursorPos(m_window, &x, &y);
	} else {
		x = 0;
		y = 0;
	}
}

vec2 InputManager::MousePosition() {
	double x, y;
	glfwGetCursorPos(m_window, &x, &y);

	return vec2(x, y);
}

InputManager::InputManager(GLFWwindow* window) {
	m_window = window;
}

void InputManager::Init(GLFWwindow* window) {
	if(m_instance == nullptr) {
		m_instance = new InputManager(window);
	}
}

void InputManager::PollEvents() {
	glfwPollEvents();
}

bool InputManager::IsKeyDown(const int key) {
	if(m_instance != nullptr && m_window != nullptr) {
		if(glfwGetKey(m_window, key) == GLFW_PRESS) {
			return true;
		}
	}

	return false;
}

bool InputManager::IsMouseButtonDown(const int key) {
	if(m_instance != nullptr && m_window != nullptr) {
		if(glfwGetMouseButton(m_window, key) == GLFW_PRESS) {
			return true;
		}
	}

	return false;
}

/*
bool InputManager::WasKeyPressed(const int key) {
	if(m_instance != nullptr && m_window != nullptr) {
		if(glfwGetKey(m_window, key)) {
			return true;
		}
	}

	return false;
}

bool InputManager::WasMouseButtonPressed(const int key) {
	if(m_instance != nullptr && m_window != nullptr) {
		if(glfwGetMouseButton(m_window, key)) {
			return true;
		}
	}

	return false;
}
*/