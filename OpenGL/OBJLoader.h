#pragma once
#include "gl_core_4_4.h"
#include "GLFW\glfw3.h"
#include "Camera.h"
#include "tiny_obj_loader.h"
#include "Colors.h"

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

	void Draw(Camera camera);
	void LoadObject(tinyobj::attrib_t& attribs, std::vector<tinyobj::shape_t>& shapes);

private:

	unsigned int m_programID;
	std::vector<OpenGLInfo> m_glInfo;
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
