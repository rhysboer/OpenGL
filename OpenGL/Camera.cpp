#include "Camera.h"

Camera::Camera() {
}

Camera::~Camera() {
}

void Camera::SetPerspective(float fov, float aspect, float near, float far) {
	m_projectionTransform = mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, -1, 0);

	m_projectionTransform[0][0] = (1 / (aspect * tan(fov / 2)));
	m_projectionTransform[1][1] = (1 / (tan(fov / 2)));

	m_projectionTransform[2][2] = -((far + near) / (far - near));
	m_projectionTransform[2][3] = -((2 * (far * near)) / (far - near));
}

void Camera::SetLookAt(vec3 from, vec3 to, vec3 up) {
	m_viewTransform = mat4(1);
}
