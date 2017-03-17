#pragma once
#include "gl_core_4_4.h"
#include "GLM\glm.hpp"
#include "GLM\ext.hpp"
#include "GLM\gtx\norm.hpp"
#include "GLFW\glfw3.h"
#include "Camera.h"

#include "ShaderLoader.h"
#include "Texture.h"

// Test
#include "Light.h"
#include "AIE\Gizmos.h"

using glm::vec2;
using glm::vec3;
using glm::vec4;

struct Vertex {
	vec4 position;
	vec4 normal;
	vec2 texCoord;
};

class Terrain {
public:
	Terrain();
	~Terrain();

	void init(unsigned int rows, unsigned int cols);
	void Draw(Camera& camera);

	void TotalTextureRepeat(uvec2 value);

	// Shadows
	void GenerateDepthBuffer();
	void GenerateShadowMap();

private:

	void GenerateGrid();

	// Total amount of times to repeat texture
	uvec2 m_textureRepeatAmount = vec2(1,1);
	unsigned int m_perlinTexture;

	unsigned int m_rows;
	unsigned int m_cols;

	unsigned int m_VAO = 0; // Vertex Array Object
	unsigned int m_VBO = 0;	// Vertex Buffer Object (Holds data of each point ect position, colour, normal)
	unsigned int m_IBO = 0; // Index Buffer Object (Which point connects to which)

	ShaderLoader m_shader = ShaderLoader();			// Regular shader for terrain
	ShaderLoader m_shadowShader = ShaderLoader();	// Shader for the shadow map 

	// Texture
	Texture* m_grass;
	Texture* m_stone;
	Texture* m_snow;
	Texture* m_sand;

	// Light
	Light* m_sun;
	vec3 lightDir;

	glm::mat4 textureSpaceOffset = glm::mat4(
		0.5f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f
	);

	unsigned int m_fbo;			// Frame Buffer Object
	unsigned int m_fboDepth;	// Texture Handler


	Vertex* aoVertices;
};

