#pragma once
#include "gl_core_4_4.h"
#include "GLM\glm.hpp"
#include "GLM\ext.hpp"
#include "GLM\gtx\norm.hpp"
#include "GLFW\glfw3.h"
#include "ShaderLoader.h"
#include "Time.h"
#include "imgui.h"

using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat4;

class PostProcessing {
public:
	PostProcessing();
	~PostProcessing();

	void BeginRender();	
	void EndRender();

private:
	ShaderLoader postShader = ShaderLoader();

	unsigned int m_fbo;
	unsigned int m_fboDepth;
	unsigned int m_fboTexture;

	unsigned int m_VAO;
	unsigned int m_VBO;

	// GUI Settings
	bool m_enabled = false;
	vec2 m_pixelSize = vec2(5, 5);
};

