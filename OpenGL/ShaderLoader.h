#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include "gl_core_4_4.h"
#include "GLFW\glfw3.h"
#include "GLM\glm.hpp"
#include "GLM\ext.hpp"

using namespace std;
using namespace glm;

using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat4;

class ShaderLoader {
public:
	ShaderLoader();
	~ShaderLoader();

	void UseProgram();
	void CreateShaderProgram(const char* vertexShaderPath, const char* fragmentShaderPath);

	void SetFloat(const char* name, const float& value);
	void SetVec2(const char* name, const vec2& value);
	void SetVec3(const char* name, const vec3& value);
	void SetVec4(const char* name, const vec4& value);
	void SetMat4(const char* name, const mat4& value);

private:
	unsigned int CreateShader(const char* path, GLenum shaderType);

	unsigned int m_programID = 0;
};

