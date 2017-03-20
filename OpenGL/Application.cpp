#include "Application.h"

Application::Application(int width, int height, const char* name) : BaseApplication::BaseApplication(width, height, name) {
}

Application::~Application() {
}

// Opengl ERROR CHECK
static void APIENTRY openglCallbackFunction( GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam ) {
	(void)source; (void)type; (void)id; (void)severity; (void)length; (void)userParam;
	fprintf(stderr, "%s\n", message);
	if(severity == GL_DEBUG_SEVERITY_HIGH) {
		fprintf(stderr, "Aborting...\n");
		abort();
	}
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

	// Background color
	glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	// Enable the debug callback
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(openglCallbackFunction, nullptr);
	glDebugMessageControl(
		GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, true
	);

	// Camera Settings
	m_camera.SetLookAt(vec3(10), vec3(0), vec3(0, 1, 0));
	m_camera.SetPerspective(glm::pi<float>() * 0.25f, 16 / 9.f, 0.1f, 1000.0f);

	// QUANTERNIONS TEST
	m_position[0] = vec3(10, 5, 10);
	m_position[1] = vec3(-10, 0, -10);
	m_rotation[0] = quat(vec3(0, -1, 0));
	m_rotation[1] = quat(vec3(0, 1, 0));

	// Terrain 
	terrain.init(50, 50);
	terrain.TotalTextureRepeat(uvec2(10, 10));

	// Water Test
	water.Init(uvec2(10, 10));
	
	//loader = new OBJLoader();
	//
	//tinyobj::attrib_t attribs;
	//std::vector<tinyobj::shape_t> shapes;
	//std::vector<tinyobj::material_t> materals;
	//std::string error;
	//
	//bool success = tinyobj::LoadObj(&attribs, &shapes, &materals, &error, "../bin/objs/Bunny.obj");
	//
	//if(success == true) {
	//	loader->LoadObject(attribs, shapes);
	//}


	//animation = new OBJAnimation();
	//animation->LoadOBJs("../bin/objs/hand/hand_00.obj", "../bin/objs/hand/hand_37.obj");


	m_sunMat = glm::translate(m_sunMat, vec3(0));
	m_earthLocal = glm::translate(m_earthLocal, vec3(5, 0, 0));
	m_moonLocal = glm::translate(m_moonLocal, vec3(2, 0, 0));

	Gizmos::create();
	return true;
}

// Update
const bool Application::Update() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Gizmos::clear();
	Gizmos::addTransform(glm::mat4(1));

	// Quit is ESC is pressed or window is closed
	if(glfwWindowShouldClose(window) == (int)true || InputManager::IsKeyDown(GLFW_KEY_ESCAPE)) {
		return false;
	}

	// Rotate Planets
	m_sunMat = glm::rotate(m_sunMat, -0.01f, vec3(0, 1, 0));
	m_earthLocal = glm::rotate(m_earthLocal, -0.01f, vec3(0, 1, 0));
	m_moonLocal = glm::rotate(m_moonLocal, 1.0f, vec3(0, 1, 0));


	m_earthMat = m_sunMat * m_earthLocal;
	m_moonMat = m_earthMat * m_moonLocal;

	Gizmos::addSphere(vec3(m_sunMat[3]), 1.f, 25, 25, Colors::Red, &m_sunMat);
	Gizmos::addSphere(vec3(m_earthMat[3]), 0.5f, 20, 20, Colors::Green, &m_earthMat);
	Gizmos::addSphere(vec3(m_moonMat[3]), 0.2f, 10, 10, Colors::Purple, &m_moonMat);

	// CUBE & QUANTERNIONS
	float s = cos((float)glfwGetTime()) * 0.5f + 0.5f;

	vec3 p = (1.0f - s) * m_position[0] + s * m_position[1];
	quat r = glm::slerp(m_rotation[0], m_rotation[1], s);
	mat4 m = glm::translate(p) * glm::toMat4(r);

	Gizmos::addTransform(m);
	Gizmos::addAABBFilled(p, vec3(.5f), Colors::Red, &m);

	// Grid
	for(int i = 0; i < 21; ++i) {
		Gizmos::addLine(vec3(-10 + i, 0, 10), vec3(-10 + i, 0, -10), i == 10 ? Colors::White : Colors::Black);
		Gizmos::addLine(vec3(10, 0, -10 + i), vec3(-10, 0, -10 + i), i == 10 ? Colors::White : Colors::Black);
	}

	// Camera Movement
	m_camera.Update();

	return true;
}

void Application::Draw() {
	Gizmos::draw(m_camera.GetProjectionView());
	LightManager::Draw(m_camera);

	//loader->Draw(m_camera);
	//animation->Draw(m_camera);
	terrain.Draw(m_camera);

	water.Draw(m_camera);
}

void Application::Shutdown() {
	Gizmos::destroy();
	LightManager::Destroy();

	glfwDestroyWindow(window);
	glfwTerminate();
}