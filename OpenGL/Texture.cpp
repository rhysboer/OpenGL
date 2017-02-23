#define STB_IMAGE_IMPLEMENTATION
#include "Texture.h"

Texture::Texture(const char* path) {
	LoadTexture(path);
}

Texture::~Texture() {
	glDeleteTextures(1, &m_texture);
}

void Texture::LoadTexture(const char * path) {
	if(path == nullptr)
		return;

	// Load texture
	unsigned char* data = stbi_load(path, &imageWidth, &imageHeight, &imageFormat, STBI_default);
	
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	stbi_image_free(data);
}

unsigned int Texture::GetTextureData() const {
	return m_texture;
}
