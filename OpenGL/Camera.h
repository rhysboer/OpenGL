#pragma once
#include "GLM\glm.hpp"
#include "GLM\ext.hpp"

using glm::vec3;
using glm::vec4;
using glm::mat4;

class Camera
{
public:
	Camera();
	~Camera();

	void Update(float deltaTime);

	void SetPerspective(float fov, float aspect, float near, float far);
	void SetLookAt(vec3 from, vec3 to, vec3 up);
	void SetPosition(vec3 position);
	
	const mat4 GetWorldTransform() const;
	const mat4 GetView() const;
	const mat4 GetProjection() const;
	const mat4 GetProjectionView() const;

protected:

	void UpdateProjectionViewTransform();

	glm::mat4 m_worldTransform;			 // global
	glm::mat4 m_viewTransform;			 // view
	glm::mat4 m_projectionTransform;	 // projection
	glm::mat4 m_projectionViewTransform; // projection * view * global
};

