#include "Light.h"



Light::Light() {
	m_color = Colors::White;
}

Light::Light(vec4 position) {
}

Light::~Light() {
}

/*
	eye		= Position of the lights view point
	center	= Direction of the light
	worldUp	= Worlds Upwards Vector
*/
void Light::LookAt(vec3 eye, vec3 center, vec3 worldUp) {

	m_lightView = glm::lookAt(eye, center, worldUp);
}

void Light::SetOrtho(vec2 left, vec2 bottom, vec2 top) {
	m_lightProjection = glm::ortho(left.x, left.y, bottom.x, bottom.y, top.x, top.y);
}

void Light::SetDirection(vec3 direction) {
	m_direction = glm::normalize(direction);
}

mat4 Light::GetViewMatrix() {
	m_lightMatrix = m_lightProjection * m_lightView;

	return mat4();
}