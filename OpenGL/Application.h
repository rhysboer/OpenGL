#pragma once
#include <iostream>
#include "BaseApplication.h"
#include "AIE\Gizmos.h"
#include "GLM\glm.hpp"
#include "GLM\ext.hpp"
#include "Colors.h"
#include "Camera.h"

using glm::vec3;
using glm::vec4;
using glm::mat4;


///////////////////////////

struct Vertex {
	vec4 position;
	vec4 colour;
};

///////////////////////////

class Application : public BaseApplication {
public:
	Application(int width, int height, const char* name);
	~Application();

	const bool Update();
	void Draw();

	const bool Startup();
	void Shutdown();

	//////////////// TESTING
	void GenerateGrid(unsigned int rows, unsigned int cols);
	void Start();

	unsigned int m_VAO;
	unsigned int m_VBO;	// Vertex Buffer Object
	unsigned int m_IBO; // Index Buffer Object

	unsigned int m_programID;

	unsigned int m_rows;
	unsigned int m_cols;

	///////////////

private:

	void Input();

	Camera camera;

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

