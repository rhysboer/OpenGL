#include "Light.h"


Light::Light() {	
	LightManager::AddLight(*this);

	m_color = Colors::White;
}

Light::~Light() {
}

/*
	eye		= Position of the lights view point
	center	= Direction of the light
	worldUp	= Worlds Upwards Vector
*/
void Light::LookAt(vec3 eye, vec3 center, vec3 worldUp) {
	m_direction = glm::normalize(eye);
	m_lightView = glm::lookAt(m_direction, center, worldUp);
}

void Light::SetOrtho(const float left, const float right, const float down, const float up, const float zNear, const float zFar) {
	m_lightProjection = glm::ortho<float>(left, right, down, up, zNear, zFar);
}

mat4 Light::GetLightMatrix() {
	m_lightMatrix = m_lightProjection * m_lightView;
	return m_lightMatrix;
}

mat4 Light::GetTextureSpaceLightMatrix() {
	m_lightMatrix = m_lightProjection * m_lightView;
	return textureSpaceOffset * m_lightMatrix;
}
