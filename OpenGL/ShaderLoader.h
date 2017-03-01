#pragma once
#include <fstream>
#include <iostream>
#include "GLFW\glfw3.h"

class ShaderLoader {
public:
	ShaderLoader();
	~ShaderLoader();

	void CreateShader(const char* path, GLenum shaderType);

private:

	unsigned int m_programID;


};

