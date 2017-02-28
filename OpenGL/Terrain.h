#pragma once
#include "gl_core_4_4.h"
#include "GLM\glm.hpp"
#include "GLM\ext.hpp"
#include "GLFW\glfw3.h"
#include "Camera.h"

#include "Texture.h"


// delet
#include <iostream>

using glm::vec2;
using glm::vec3;
using glm::vec4;

struct Vertex {
	vec4 position;
	vec2 textPos;
};

// vec4 color

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
	unsigned int m_VBO = 0;	// Vertex Buffer Object (Holds data of each point ect position, colour, normal)
	unsigned int m_IBO = 0; // Index Buffer Object (Which point connects to which)

	unsigned int m_programID;

	// Texture
	Texture* m_texture;
};

