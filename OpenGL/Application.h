#pragma once
#include <iostream>
#include "BaseApplication.h"
#include "AIE\Gizmos.h"
#include "GLM\glm.hpp"
#include "GLM\ext.hpp"
#include "Colors.h"
#include "Camera.h"

// Quanternion
#include <GLM\gtc\quaternion.hpp>
#include <GLM\gtx\quaternion.hpp>

#include "Terrain.h"

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

	Terrain terrain = Terrain();

	void Input();

	Camera camera;


	// CUBE
	mat4 m_cubeMat = mat4(1);
	vec3 m_position[2];
	quat m_rotation[2];


	mat4 m_sunMat = mat4(1);

	mat4 m_earthMat = mat4(1);
	mat4 m_earthLocal = mat4(1);

	mat4 m_moonMat = mat4(1);
	mat4 m_moonLocal = mat4(1);

	// Rotation Matrices
	mat4 sunRotation = mat4(1);
	mat4 earthRotation = mat4(1);
	mat4 moonRotation = mat4(1);

	// Delta Time (Move to own class)
	float previousTime = 0;
	float currentTime = 0;
	float deltaTime = 0;
};

