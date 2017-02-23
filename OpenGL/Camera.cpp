#include "Camera.h"

Camera::Camera() {
	m_rotationMat		= mat4(1);
	m_worldMat			= mat4(1);
	m_viewMat			= mat4(1);
	m_projectionMat		= mat4(1);
	m_projectionViewMat	= mat4(1);
}

Camera::~Camera() {
}

void Camera::Update(float deltaTime) {
}

void Camera::SetPerspective(float fov, float aspect, float _near, float _far) {
	m_projectionMat = mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0);                                                           

	m_projectionMat[0][0] = (1 / (aspect * tan(fov / 2)));
	m_projectionMat[1][1] = (1 / (tan(fov / 2)));

	m_projectionMat[2][2] = -(_far + _near) / (_far - _near);
	m_projectionMat[3][2] = -(2 * _far * _near) / (_far - _near);
}

void Camera::SetLookAt(vec3 towards, vec3 center, vec3 worldUp) {
	vec3 direction(glm::normalize(center - towards)); // Cameras reverse facing direction
	vec3 rightAngle(glm::normalize(glm::cross(direction, worldUp))); // Cameras right angle
	vec3 up(cross(rightAngle, direction)); // Cameras up axis

	m_worldMat[0][0] = rightAngle.x;
	m_worldMat[1][0] = rightAngle.y;
	m_worldMat[2][0] = rightAngle.z;

	m_worldMat[0][1] = up.x;
	m_worldMat[1][1] = up.y;
	m_worldMat[2][1] = up.z;

	m_worldMat[0][2] = -direction.x;
	m_worldMat[1][2] = -direction.y;
	m_worldMat[2][2] = -direction.z;

	m_worldMat[3][0] = -glm::dot(rightAngle, towards);                
	m_worldMat[3][1] = -glm::dot(up, towards);                        
	m_worldMat[3][2] = glm::dot(direction, towards);         

	m_worldMat = glm::inverse(m_worldMat);
}						        

void Camera::SetPosition(vec3 position) {
	InverseWorldTransform();
	m_worldMat[3][0] = -position.x;
	m_worldMat[3][1] = -position.y;
	m_worldMat[3][2] = -position.z;
	InverseWorldTransform();

	UpdateProjectionViewTransform();
}

void Camera::Move(vec3 translate) {
	InverseWorldTransform();
	m_worldMat[3][0] += -translate.x;
	m_worldMat[3][1] += -translate.y;
	m_worldMat[3][2] += -translate.z;
	InverseWorldTransform();

	UpdateProjectionViewTransform();
}

void Camera::Rotate(float angle, vec3 axis) {
	if(axis != vec3(0)) {
		vec3 axisNorm = glm::normalize(axis);
		mat4 rotation = mat4(1);

		rotation = glm::rotate(rotation, angle, axis);

		m_worldMat *= glm::inverse(rotation);

		UpdateProjectionViewTransform();
	}
}

const mat4 Camera::GetWorldTransform() const {
	return m_worldMat;
}

const mat4 Camera::GetView() const {
	return m_viewMat;
}

const mat4 Camera::GetProjection() const {
	return m_projectionMat;
}

const mat4 Camera::GetProjectionView() {
	return UpdateProjectionViewTransform();
}

void Camera::InverseWorldTransform() {
	m_worldMat = glm::inverse(m_worldMat);
}

mat4 Camera::UpdateProjectionViewTransform() {
	m_viewMat = glm::inverse(m_worldMat);
	return m_projectionViewMat = m_projectionMat * m_viewMat;
}
