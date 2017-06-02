#pragma once
#include "PhysicsObject.h"
#include "Colours.h"
#include "AIE\Gizmos.h"

#include "GLM\gtx\rotate_vector.hpp"

class Plane : public PhysicsObject {
public:
	//Plane();
	Plane(glm::vec2 normal, float height, float rotation = 0.0f);
	~Plane();

	virtual void FixedUpdate(glm::vec2 gravity, float timeStep);
	virtual void Debug(int id) {};
	virtual void MakeGizmo();
	virtual void ResetPosition() {};

	// Getters
	glm::vec2 GetNormal() { return m_normal; }
	float GetDistance() { return m_distanceToOrigin; }

protected:

	glm::vec2 m_normal;
	float m_distanceToOrigin;
};

