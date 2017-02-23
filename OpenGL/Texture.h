#pragma once
#include "STB\stb_image.h"
#include "GLFW\glfw3.h"

class Texture {
public:
	Texture(const char* path);
	~Texture();

	void LoadTexture(const char* path);
	unsigned int GetTextureData() const;

private:

	int imageHeight = 0;
	int imageWidth = 0;
	int imageFormat = 0;

	unsigned int m_texture = 0;
};

