#pragma once

#include "STB\stb_image.h"

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

	void init(unsigned int rows, unsigned int cols);
	void Draw(Camera& camera);

private:

	void GenerateGrid();

	unsigned int m_rows;
	unsigned int m_cols;

	unsigned int m_VAO = 0; // Vertex Array Object
	unsigned int m_VBO = 0;	// Vertex Buffer Object
	unsigned int m_IBO = 0; // Index Buffer Object

	unsigned int m_programID;

	// TEXTURE
	int imageWidth = 0;
	int imageHeight = 0;
	int imageFormat = 0;

	unsigned int m_texture = 0;
};

