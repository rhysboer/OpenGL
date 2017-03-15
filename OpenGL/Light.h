#pragma once
#include "GLM\glm.hpp"
#include "GLM\ext.hpp"
#include "GLM\gtx\norm.hpp"

#include "Colors.h"

using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat4;

class Light {
public:
	Light();
	Light(vec4 position);
	~Light();

	void LookAt(vec3 eye, vec3 center, vec3 worldUp = vec3(0, 1, 0));
	void SetOrtho(vec2 left, vec2 up, vec2 down);

	void SetDirection(vec3 direction);
	void SetPosition(const vec4 position);
	void SetColor(const vec4 color);

	mat4 GetViewMatrix();


	// temp
	const mat4 GetTextureSpaceOffset() { return TEXTURE_SPACE_OFFSET; }

private:

	vec4 m_color;
	vec3 m_direction;

	mat4 m_lightProjection;
	mat4 m_lightView;
	mat4 m_lightMatrix;

	// Put into direction Light class
	const mat4 TEXTURE_SPACE_OFFSET = mat4(
		0.5f,	0,		0,		0,
		0,		0.5f,	0,		0,
		0,		0,		0.5f,	0,
		0.5f,	0.5f,	0.5f,	1.0f
	);
};

