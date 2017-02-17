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

	virtual void Update(float deltaTime);

	void SetPerspective(float fov, float aspect, float _near, float _far);
	void SetLookAt(vec3 towards, vec3 center, vec3 worldUp);
	void SetPosition(vec3 position);
	void Move(vec3 translate);

	const mat4 GetWorldTransform() const;
	const mat4 GetView() const;
	const mat4 GetProjection() const;
	const mat4 GetProjectionView();

protected:	
	void InverseWorldTransform();
	mat4 UpdateProjectionViewTransform();

	glm::mat4 m_worldTransform;			 // global / model position
	glm::mat4 m_viewTransform;			 // view
	glm::mat4 m_projectionTransform;	 // projection
	glm::mat4 m_projectionViewTransform; // projection * view
};

