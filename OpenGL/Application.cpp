#include "Application.h"

Application::Application(int width, int height, const char* name) : BaseApplication::BaseApplication(width, height, name) {
}

Application::~Application() {
}

const bool Application::Update() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Gizmos::clear();
	Gizmos::addTransform(glm::mat4(1));

	currentTime = (float)glfwGetTime();


	if(glfwWindowShouldClose(window) == true || glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		return false;
	}

	// Rotate Planets
	m_sunRTransform = glm::rotate(m_sunTransform, 1.0f, vec3(0, 1, 0));
	m_earthRTransform = glm::rotate(m_earthRTransform, 1.0f, vec3(0, 1, 0));
	m_moonRTransform = glm::rotate(m_moonRTransform, 1.0f, vec3(0, 1, 0));

	m_sunTransform = m_sunLocal * m_sunRTransform;
	m_earthTransform = m_sunLocal* m_earthLocal * m_sunRTransform * m_earthRTransform;

	m_earthTransform *= glm::inverse(m_sunTransform);


	Gizmos::addSphere(vec3(m_sunTransform[3]), 1.f, 25, 25, Colors::red, &m_sunTransform);
	Gizmos::addSphere(vec3(m_earthTransform[3]), 0.5f, 20, 20, Colors::green, &m_earthTransform);
	Gizmos::addSphere(vec3(m_moonTransform[3]), 0.2f, 10, 10, Colors::purple, &m_moonTransform);

	// Grid
	for(int i = 0; i < 21; ++i) {
		Gizmos::addLine(vec3(-10 + i, 0, 10), vec3(-10 + i, 0, -10), i == 10 ? Colors::white : Colors::black);
		Gizmos::addLine(vec3(10, 0, -10 + i), vec3(-10, 0, -10 + i), i == 10 ? Colors::white : Colors::black);
	}


	// Camera Movement
	Input();


	// Delta Time
	deltaTime = currentTime - previousTime;
	previousTime = currentTime;

	return true;
}

void Application::Draw() {
	Gizmos::draw(projection * view);

	glfwSwapBuffers(window);
	glfwPollEvents();
}

const bool Application::Startup() {
	if(window == nullptr) {
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window);

	if(ogl_LoadFunctions() == ogl_LOAD_FAILED) {
		glfwDestroyWindow(window);
		glfwTerminate();
		return false;
	}

	// Camera
	view = glm::lookAt(vec3(10, 10, 10), vec3(0), vec3(0, 1, 0));
	projection = glm::perspective(glm::pi<float>() * 0.25f, 16 / 9.f, 0.1f, 1000.0f);

	// Background color
	glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	m_sunLocal = glm::translate(m_sunLocal, vec3(0));
	m_earthLocal = glm::translate(m_earthLocal, vec3(5, 0, 0));
	m_moonTransform = glm::translate(m_moonTransform, vec3(2, 0, 0));

	// Delta Time
	currentTime = (float)glfwGetTime();
	
	Gizmos::create();
	return true;
}

void Application::Shutdown() {
	Gizmos::destroy();
	glfwDestroyWindow(window);
	glfwTerminate();
}

void Application::Input() {
	view = glm::inverse(view);

	// FORWARD
	if(glfwGetKey(window, GLFW_KEY_W)) {
		view = glm::translate(view, vec3(0, 0, -3) * deltaTime);
	}
	
	// BACKWARDS
	if(glfwGetKey(window, GLFW_KEY_S)) {
		view = glm::translate(view, vec3(0, 0, 3) * deltaTime);
	}
	
	// LEFT
	if(glfwGetKey(window, GLFW_KEY_A)) {
		view = glm::translate(view, vec3(-3, 0, 0) * deltaTime);
	}
	
	// RIGHT
	if(glfwGetKey(window, GLFW_KEY_D)) {
		view = glm::translate(view, vec3(3, 0, 0) * deltaTime);
	}
	
	// UP
	if(glfwGetKey(window, GLFW_KEY_E)) {
		view = glm::translate(view, vec3(0, 3, 0) * deltaTime);
	}
	
	// DOWN
	if(glfwGetKey(window, GLFW_KEY_Q)) {
		view = glm::translate(view, vec3(0, -3, 0) * deltaTime);
	}
	
	view = glm::inverse(view);
}
