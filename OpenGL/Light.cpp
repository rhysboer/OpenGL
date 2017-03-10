#include "Light.h"



Light::Light() {
}

Light::Light(vec4 position) {
}


Light::~Light() {
}

void Light::LookAt(vec3 direction, vec3 center, vec3 worldUp) {
	m_lightView = glm::lookAt(direction, center, worldUp);
}

void Light::SetOrtho(vec2 left, vec2 bottom, vec2 top) {
	m_lightProjection = glm::ortho(left.x, left.y, bottom.x, bottom.y, top.x, top.y);
}
