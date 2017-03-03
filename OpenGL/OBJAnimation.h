#pragma once
#include "gl_core_4_4.h"
#include "GLFW\glfw3.h"
#include "tiny_obj_loader.h"
#include "Camera.h"
#include "ShaderLoader.h"

struct OBVertex {
	float x, y, z;
	float nx, ny, nz;
	float u, v;
};

struct GLInfo {
	unsigned int m_VAO;
	unsigned int m_VBO1;
	unsigned int m_VBO2;
	unsigned int m_faceCount;
};

class OBJAnimation {
public:
	OBJAnimation();
	~OBJAnimation();

	bool LoadOBJs(const char* path1, const char* path2);
	void Draw(Camera camera);

private:

	unsigned int CreateVertexBuffer(const tinyobj::attrib_t& attribs, const tinyobj::shape_t& shape);

	std::vector<GLInfo> m_meshes;

	ShaderLoader shader = ShaderLoader();
};

