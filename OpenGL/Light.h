#pragma once
#include "LightManager.h"
#include "gl_core_4_4.h"
#include "GLFW\glfw3.h"
#include "GLM\glm.hpp"
#include "GLM\ext.hpp"
#include "GLM\gtx\norm.hpp"

#include "Colours.h"

using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat4;

class Light {
public:
	Light();
	~Light();

	//virtual void Draw(mat4 cameraView);

	void LookAt(vec3 eye, vec3 center, vec3 worldUp = vec3(0, 1, 0));
	void SetOrtho(const float left, const float right, const float bottom, const float top, const float zNear, const float zFar);

	void SetPosition(const vec4 position);
	void SetColor(const vec4 color);

	mat4 GetLightMatrix();
	mat4 GetTextureSpaceLightMatrix();


	// temp
	const mat4 GetTextureSpaceOffset() { return textureSpaceOffset; }
	vec3 GetDirection() { return m_direction; }

private:

	vec4 m_color;
	vec3 m_direction;

	mat4 m_lightProjection;
	mat4 m_lightView;
	mat4 m_lightMatrix;

	// Put into direction Light class
	glm::mat4 textureSpaceOffset = glm::mat4(
		0.5f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f
	);
};

