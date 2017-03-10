#pragma once
#include "gl_core_4_4.h"
#include "GLM\glm.hpp"
#include "GLM\ext.hpp"
#include "GLM\gtx\norm.hpp"
#include "GLFW\glfw3.h"
#include "Camera.h"

#include "ShaderLoader.h"
#include "Texture.h"

using glm::vec2;
using glm::vec3;
using glm::vec4;

struct WaterVertex {
	vec4 position;
	vec4 normal;
	vec2 texCoord;
};

class Water {
public:
	Water();
	~Water();

	void Init(uvec2 size);
	void Draw(Camera& camera);

private:
	// Build this mesh for the water
	void BuildMesh();

	// Size
	uvec2 m_size;

	// Wave Settings
	float m_waveHeight = 0.3f;
	float m_waveSpeed = 0.7f;
	float m_textureScrollSpeed = 0.05f;

	unsigned int m_repeatCount = 3;

	// Water Shader
	ShaderLoader m_shader = ShaderLoader();

	// Texture
	Texture* m_waterTexture;

	unsigned int m_VAO = 0; // Vertex Array Object
	unsigned int m_VBO = 0;	// Vertex Buffer Object (Holds data of each point ect position, colour, normal)
	unsigned int m_IBO = 0; // Index Buffer Object (Which point connects to which)
};

