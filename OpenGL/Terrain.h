#pragma once
#include "gl_core_4_4.h"
#include "GLM\glm.hpp"
#include "GLM\ext.hpp"
#include "GLFW\glfw3.h"
#include "Camera.h"

using glm::vec3;
using glm::vec4;

struct Vertex {
	vec4 position;
	vec4 colour;
};

class Terrain {
public:
	Terrain();
	~Terrain();

	void Draw(Camera& camera);

private:

	void GenerateGrid(unsigned int rows, unsigned int cols);

	unsigned int m_VAO; 
	unsigned int m_VBO;	// Vertex Buffer Object
	unsigned int m_IBO; // Index Buffer Object

	unsigned int m_programID;
};

