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

	// Mouse
	UpdateMousePosition();

	// Camera
	m_camera.SetLookAt(vec3(10), vec3(0), vec3(0, 1, 0));
	m_camera.SetPerspective(glm::pi<float>() * 0.25f, 16 / 9.f, 0.1f, 1000.0f);

	// QUANTERNIONS TEST
	m_position[0] = vec3(10, 5, 10);
	m_position[1] = vec3(-10, 0, -10);
	m_rotation[0] = quat(vec3(0, -1, 0));
	m_rotation[1] = quat(vec3(0, 1, 0));

	// Background color
	glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	// Terrain 
	terrain.init(4, 4);

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

	// Quit is ESC is pressed or window is closed
	if(glfwWindowShouldClose(window) == (int)true || glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		return false;
	}

	// Update Mouse
	UpdateMousePosition();

	// Rotate Planets
	m_sunMat = glm::rotate(m_sunMat, -0.01f, vec3(0, 1, 0));
	m_earthLocal = glm::rotate(m_earthLocal, -0.01f, vec3(0, 1, 0));
	m_moonLocal = glm::rotate(m_moonLocal, 1.0f, vec3(0, 1, 0));


	m_earthMat = m_sunMat * m_earthLocal;
	m_moonMat = m_earthMat * m_moonLocal;

	//Gizmos::addSphere(vec3(m_sunMat[3]), 1.f, 25, 25, Colors::red, &m_sunMat);
	Gizmos::addSphere(vec3(m_earthMat[3]), 0.5f, 20, 20, Colors::green, &m_earthMat);
	Gizmos::addSphere(vec3(m_moonMat[3]), 0.2f, 10, 10, Colors::purple, &m_moonMat);

	// CUBE & QUANTERNIONS
	float s = cos((float)glfwGetTime()) * 0.5f + 0.5f;

	vec3 p = (1.0f - s) * m_position[0] + s * m_position[1];
	quat r = glm::slerp(m_rotation[0], m_rotation[1], s);
	mat4 m = glm::translate(p) * glm::toMat4(r);

	Gizmos::addTransform(m);
	Gizmos::addAABBFilled(p, vec3(.5f), Colors::red, &m);

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
	Gizmos::draw(m_camera.GetProjectionView());

	terrain.Draw(m_camera);

	glfwSwapBuffers(window);
	glfwPollEvents();
}

void Application::Shutdown() {
	Gizmos::destroy();
	glfwDestroyWindow(window);
	glfwTerminate();
}

void Application::Input() {
	float speedModifier = 1;

	if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)) {
		speedModifier = 3;
	}

	// FORWARD
	if(glfwGetKey(window, GLFW_KEY_W)) {
		m_camera.Move(vec3(0, 0, -3) * speedModifier * deltaTime);
	}
	
	// BACKWARDS
	if(glfwGetKey(window, GLFW_KEY_S)) {
		m_camera.Move(vec3(0, 0, 3) * speedModifier * deltaTime);
	}
	
	// LEFT
	if(glfwGetKey(window, GLFW_KEY_A)) {
		m_camera.Move(vec3(-3, 0, 0) * speedModifier * deltaTime);
	}
	
	// RIGHT
	if(glfwGetKey(window, GLFW_KEY_D)) {
		m_camera.Move(vec3(3, 0, 0) * speedModifier * deltaTime);
	}
	
	// UP
	if(glfwGetKey(window, GLFW_KEY_E)) {
		m_camera.Move(vec3(0, 3, 0) * speedModifier * deltaTime);
	}
	
	// DOWN
	if(glfwGetKey(window, GLFW_KEY_Q)) {
		m_camera.Move(vec3(0, -3, 0) * speedModifier * deltaTime);
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1)) {
		vec3 mousePosition = GetMouseCameraMovement();
		if(mousePosition != vec3(0)) {
			m_camera.Rotate(3.0f * deltaTime, mousePosition);
		}
	}
}

void Application::UpdateMousePosition() {
	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);

	oldPos = currPos;
	currPos = vec3((float)mouseX, (float)mouseY, 0);
}

vec3 Application::GetMouseCameraMovement() {
	vec3 pos = currPos - oldPos;

	if(pos == vec3(0)) {
		return vec3(0);
	}

	vec3 temp = pos;
	pos.y = temp.x;
	pos.x = temp.y;

	return pos;
}
