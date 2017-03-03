#pragma once
#include "ShaderLoader.h"
#include "Camera.h"
#include "tiny_obj_loader.h"
#include "Colors.h"

#include "Terrain.h"

struct OpenGLInfo {
	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_faceCount;
};

struct OBJVertex {
	float x, y, z; // Position
	float nx, ny, nz; // Normal
	float u, v; // Texture Coordinates
};

class OBJLoader {
public:
	OBJLoader();
	~OBJLoader();

	void Draw(Camera camera); // void Draw(Camera camera);
	void LoadObject(tinyobj::attrib_t& attribs, std::vector<tinyobj::shape_t>& shapes);

private:

	ShaderLoader shader = ShaderLoader();

	// Generate Shadow
	ShaderLoader shadow = ShaderLoader();

	unsigned int m_programID;
	std::vector<OpenGLInfo> m_glInfo;

	// For Shadow
	unsigned int m_fbo;
	unsigned int m_fboDepth;

	glm::mat4 m_lightMatrix;
	glm::mat4 textureSpaceOffset = glm::mat4(
		0.5f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f
	);
};

/*
// OBJECT LOADER

loader = new OBJLoader();

tinyobj::attrib_t attribs;
std::vector<tinyobj::shape_t> shapes;
std::vector<tinyobj::material_t> materals;
std::string error;

bool success = tinyobj::LoadObj(&attribs, &shapes, &materals, &error, "../bin/objs/bunny.obj");

if(success == true) {
loader->LoadObject(attribs, shapes);
}
*/
