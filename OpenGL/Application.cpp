#include "Application.h"

Application::Application(int width, int height, const char* name) : BaseApplication::BaseApplication(width, height, name) {
}

Application::~Application() {
}

// Start Up
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
	camera.SetLookAt(vec3(10), vec3(0), vec3(0, 1, 0));
	camera.SetPerspective(glm::pi<float>() * 0.25f, 16 / 9.f, 0.1f, 1000.0f);

	//camera.Rotate(1.5f, vec3(1, 0, 1));

	// Background color
	glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	terrain.init(10, 10);

	m_sunMat = glm::translate(m_sunMat, vec3(0));
	m_earthLocal = glm::translate(m_earthLocal, vec3(5, 0, 0));
	m_moonLocal = glm::translate(m_moonLocal, vec3(2, 0, 0));

	// Delta Time
	currentTime = (float)glfwGetTime();

	Gizmos::create();
	return true;
}

// Update
const bool Application::Update() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Gizmos::clear();
	Gizmos::addTransform(glm::mat4(1));

	currentTime = (float)glfwGetTime();

	if(glfwWindowShouldClose(window) == (int)true || glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		return false;
	}

	// Rotate Planets
	m_sunMat = glm::rotate(m_sunMat, -0.01f, vec3(0, 1, 0));
	m_earthLocal = glm::rotate(m_earthLocal, -0.01f, vec3(0, 1, 0));
	m_moonLocal = glm::rotate(m_moonLocal, 1.0f, vec3(0, 1, 0));

		
	m_earthMat = m_sunMat * m_earthLocal;
	m_moonMat = m_earthMat * m_moonLocal;

	Gizmos::addSphere(vec3(m_sunMat[3]), 1.f, 25, 25, Colors::red, &m_sunMat);
	Gizmos::addSphere(vec3(m_earthMat[3]), 0.5f, 20, 20, Colors::green, &m_earthMat);
	Gizmos::addSphere(vec3(m_moonMat[3]), 0.2f, 10, 10, Colors::purple, &m_moonMat);

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
	Gizmos::draw(camera.GetProjectionView());

	//terrain.Draw(camera);

	glfwSwapBuffers(window);
	glfwPollEvents();
}

void Application::Shutdown() {
	Gizmos::destroy();
	glfwDestroyWindow(window);
	glfwTerminate();
}

void Application::Input() {
	// FORWARD
	if(glfwGetKey(window, GLFW_KEY_W)) {
		camera.Move(vec3(0, 0, -3) * deltaTime);
	}
	
	// BACKWARDS
	if(glfwGetKey(window, GLFW_KEY_S)) {
		camera.Move(vec3(0, 0, 3) * deltaTime);
	}
	
	// LEFT
	if(glfwGetKey(window, GLFW_KEY_A)) {
		camera.Move(vec3(-3, 0, 0) * deltaTime);
	}
	
	// RIGHT
	if(glfwGetKey(window, GLFW_KEY_D)) {
		camera.Move(vec3(3, 0, 0) * deltaTime);
	}
	
	// UP
	if(glfwGetKey(window, GLFW_KEY_E)) {
		camera.Move(vec3(0, 3, 0) * deltaTime);
	}
	
	// DOWN
	if(glfwGetKey(window, GLFW_KEY_Q)) {
		camera.Move(vec3(0, -3, 0) * deltaTime);
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1)) {
		camera.Rotate(1.5f * deltaTime, vec3(1,0,0));
	}
}
