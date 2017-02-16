#pragma once
#include <iostream>
#include "BaseApplication.h"
#include "AIE\Gizmos.h"
#include "GLM\glm.hpp"
#include "GLM\ext.hpp"
#include "Colors.h"

using glm::vec3;
using glm::vec4;
using glm::mat4;

class Application : public BaseApplication {
public:
	Application(int width, int height, const char* name);
	~Application();

	const bool Update();
	void Draw();

	const bool Startup();
	void Shutdown();
private:

	void Input();

	// Camera
	mat4 view;
	mat4 projection;

	mat4 m_sunTransform = mat4(1);
	mat4 m_sunLocal = mat4(1);
	mat4 m_sunRTransform = mat4(1);

	mat4 m_earthTransform = mat4(1);
	mat4 m_earthLocal = mat4(1);
	mat4 m_earthRTransform = mat4(1);

	mat4 m_moonTransform = mat4(1);
	mat4 m_moonRTransform = mat4(1);


	// Rotation Matrices
	mat4 sunRotation = mat4(1);
	mat4 earthRotation = mat4(1);
	mat4 moonRotation = mat4(1);

	// Delta Time (Move to own class)
	float previousTime = 0;
	float currentTime = 0;
	float deltaTime = 0;
};

