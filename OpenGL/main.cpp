#include "Application.h"

int main() {
	BaseApplication* app = new Application(1280, 720, "OpenGL");
	if(app->Startup() == true) {
		while(app->Update() == true) {
			app->Draw();
		}

		app->Shutdown();
	}

	delete app;
	return 0;

	//if (glfwInit() == false)
	//	return -1;

	//GLFWwindow* window = glfwCreateWindow(1280, 720, "OpenGL", nullptr, nullptr);

	//if (window == nullptr) {
	//	glfwTerminate();
	//	return -2;
	//}

	//glfwMakeContextCurrent(window);

	//if (ogl_LoadFunctions() == ogl_LOAD_FAILED) {
	//	glfwDestroyWindow(window);
	//	glfwTerminate();
	//	return -3;
	//}

	//Gizmos::create();

	//// Camera
	//mat4 view = glm::lookAt(vec3(10, 10, 10), vec3(0), vec3(0,1,0));
	//mat4 projection = glm::perspective(glm::pi<float>() * 0.25f, 16 / 9.f, 0.1f, 1000.0f);

	//mat4 inverse = view;


	//auto major = ogl_GetMajorVersion();
	//auto minor = ogl_GetMinorVersion();
	//printf("GL: %i.%i\n", major, minor);

	//// Rotation Matrices
	//mat4 sunRotation = mat4(1);
	//mat4 earthRotation = mat4(1);
	//mat4 moonRotation = mat4(1);

	//// Delta Time
	//float previousTime = 0;
	//float currentTime = (float)glfwGetTime();
	//float deltaTime = 0;

	//earthRotation = glm::translate(earthRotation, vec3(5, 0, 0));
	//moonRotation = glm::translate(moonRotation, vec3(2, 0, 0));

	//glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
	//glEnable(GL_DEPTH_TEST);
	//while (glfwWindowShouldClose(window) == false && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS) {
	//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//	Gizmos::clear();
	//	Gizmos::addTransform(glm::mat4(1));

	//	sunRotation = glm::rotate(sunRotation, 0.005f, vec3(0,1,0));
	//	earthRotation = glm::rotate(earthRotation, 0.01f, vec3(0, 1, 0));
	//	moonRotation = glm::rotate(moonRotation, 10.0f, vec3(0, 1, 0));
	//
	//	mat4 earth = sunRotation * earthRotation;
	//	mat4 moon =  earth * moonRotation;

	//	// colors
	//	vec4 white(1);
	//	vec4 black(0, 0, 0, 1);

	//	Gizmos::addSphere(vec3(0, 0, 0), 1.f, 25, 25, vec4(1, 0, 0, 1), &sunRotation);
	//	Gizmos::addSphere(vec3(earth[3].x, earth[3].y, earth[3].z),0.5f, 20, 20, vec4(0, 0, 1, 1), &earth);
	//	Gizmos::addSphere(vec3(moon[3].x, moon[3].y, moon[3].z), 0.2f, 10, 10, vec4(1, 0, 1, 1), &moon);

	//	// Grid
	//	for (int i = 0; i < 21; ++i) {
	//		Gizmos::addLine(vec3(-10 + i, 0, 10), vec3(-10 + i, 0, -10), i == 10 ? white : black);
	//		Gizmos::addLine(vec3(10, 0, -10 + i), vec3(-10, 0, -10 + i), i == 10 ? white : black);
	//	}


	//	inverse = glm::inverse(inverse);
	//	if(glfwGetKey(window, GLFW_KEY_W)) {
	//		inverse = glm::translate(inverse, vec3(0, 0, -3) * deltaTime);
	//	}

	//	if(glfwGetKey(window, GLFW_KEY_S)) {
	//		inverse = glm::translate(inverse, vec3(0, 0, 3) * deltaTime);
	//	}

	//	if(glfwGetKey(window, GLFW_KEY_A)) {
	//		inverse = glm::translate(inverse, vec3(-3, 0, 0) * deltaTime);
	//	}

	//	if(glfwGetKey(window, GLFW_KEY_D)) {
	//		inverse = glm::translate(inverse, vec3(3, 0, 0) * deltaTime);
	//	}

	//	if(glfwGetKey(window, GLFW_KEY_E)) {
	//		inverse = glm::translate(inverse, vec3(0, 3, 0) * deltaTime);
	//	}

	//	if(glfwGetKey(window, GLFW_KEY_Q)) {
	//		inverse = glm::translate(inverse, vec3(0, -3, 0) * deltaTime);
	//	}

	//	inverse = glm::inverse(inverse);


	//	Gizmos::draw(projection * inverse);

	//	// Delta Time
	//	currentTime = (float)glfwGetTime();
	//	deltaTime = currentTime - previousTime;
	//	previousTime = currentTime;

	//	glfwSwapBuffers(window);
	//	glfwPollEvents();
	//}

	//Gizmos::destroy();
	//glfwDestroyWindow(window);
	//glfwTerminate();

	//return 0;
}