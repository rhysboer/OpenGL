#pragma once
#include "GLM\glm.hpp"
#include "GLM\ext.hpp"

// Quanternion
#include <GLM\gtc\quaternion.hpp>
#include <GLM\gtx\quaternion.hpp>

#include "Time.h"
#include "InputManager.h"

using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat4;
using glm::quat;

class Camera
{
public:
	Camera();
	~Camera();

	virtual void Update();

	void SetPerspective(float fov, float aspect, float _near, float _far);
	void SetLookAt(vec3 towards, vec3 center, vec3 worldUp);
	void SetPosition(vec3 position);
	void Move(vec3 translate);
	void Rotate(float angle, vec3 axis);

	void SetRotationSpeed(float speed);

	const mat4 GetWorldTransform() const;
	const mat4 GetView() const;
	const mat4 GetProjection() const;
	const mat4 GetProjectionView();
	const vec3 GetPosition();

protected:	
	void InverseWorldTransform();
	mat4 UpdateProjectionViewTransform();

	mat4 m_worldMat;			// global / model position
	mat4 m_viewMat;				// view
	mat4 m_projectionMat;		// projection
	mat4 m_projectionViewMat;	// projection * view


	float m_rotationSpeed;		// Camera Rotation Speed
};

