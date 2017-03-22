#pragma once
#include "ShaderLoader.h"
#include "Camera.h"
#include "tiny_obj_loader.h"
#include "Colors.h"


#include "Texture.h"
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
	void LoadObject(const char* path);

private:

	ShaderLoader shader = ShaderLoader();
	ShaderLoader postShader = ShaderLoader();

	unsigned int m_programID;
	std::vector<OpenGLInfo> m_glInfo;

	unsigned int m_fbo;
	unsigned int m_fboDepth;
	unsigned int m_fboTexture;

	unsigned int m_VAO;
	unsigned int m_VBO;
};