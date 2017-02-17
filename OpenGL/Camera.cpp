#include "Camera.h"

Camera::Camera() {
	m_worldTransform			= mat4(1);
	m_viewTransform				= mat4(1);
	m_projectionTransform		= mat4(1);
	m_projectionViewTransform	= mat4(1);
}

Camera::~Camera() {
}

void Camera::Update(float deltaTime) {
}

void Camera::SetPerspective(float fov, float aspect, float _near, float _far) {
	m_projectionTransform = mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0);                                                           

	m_projectionTransform[0][0] = (1 / (aspect * tan(fov / 2)));
	m_projectionTransform[1][1] = (1 / (tan(fov / 2)));

	m_projectionTransform[2][2] = -(_far + _near) / (_far - _near);
	m_projectionTransform[3][2] = -(2 * _far * _near) / (_far - _near);
}

void Camera::SetLookAt(vec3 towards, vec3 center, vec3 worldUp) {
	vec3 direction(glm::normalize(center - towards)); // Cameras reverse facing direction
	vec3 rightAngle(glm::normalize(glm::cross(direction, worldUp))); // Cameras right angle
	vec3 up(cross(rightAngle, direction)); // Cameras up axis

	m_worldTransform[0][0] = rightAngle.x;
	m_worldTransform[1][0] = rightAngle.y;
	m_worldTransform[2][0] = rightAngle.z;

	m_worldTransform[0][1] = up.x;
	m_worldTransform[1][1] = up.y;
	m_worldTransform[2][1] = up.z;

	m_worldTransform[0][2] = -direction.x;
	m_worldTransform[1][2] = -direction.y;
	m_worldTransform[2][2] = -direction.z;

	m_worldTransform[3][0] = -glm::dot(rightAngle, towards);                
	m_worldTransform[3][1] = -glm::dot(up, towards);                        
	m_worldTransform[3][2] = glm::dot(direction, towards);         

	m_worldTransform = glm::inverse(m_worldTransform);
}						        

void Camera::SetPosition(vec3 position) {
	InverseWorldTransform();
	m_worldTransform[3][0] = -position.x;
	m_worldTransform[3][1] = -position.y;
	m_worldTransform[3][2] = -position.z;
	InverseWorldTransform();

	UpdateProjectionViewTransform();
}

void Camera::Move(vec3 translate) {
	InverseWorldTransform();
	m_worldTransform[3][0] += -translate.x;
	m_worldTransform[3][1] += -translate.y;
	m_worldTransform[3][2] += -translate.z;
	InverseWorldTransform();

	UpdateProjectionViewTransform();
}

const mat4 Camera::GetWorldTransform() const {
	return m_worldTransform;
}

const mat4 Camera::GetView() const {
	return m_viewTransform;
}

const mat4 Camera::GetProjection() const {
	return m_projectionTransform;
}

const mat4 Camera::GetProjectionView() {
	return UpdateProjectionViewTransform();
}

void Camera::InverseWorldTransform() {
	m_worldTransform = glm::inverse(m_worldTransform);
}

mat4 Camera::UpdateProjectionViewTransform() {
	m_viewTransform = glm::inverse(m_worldTransform);
	return m_projectionViewTransform = m_projectionTransform * m_viewTransform;
}
