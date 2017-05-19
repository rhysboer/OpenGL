#pragma once
#include "Rigidbody.h"
#include "AIE\Gizmos.h"
#include "AABB.h"

class Box : public Rigidbody {
public:
	Box();
	Box(glm::vec2 position, float length, float height, float mass, glm::vec4 colour = glm::vec4(1));
	~Box();

	virtual void FixedUpdate(glm::vec2 gravity, float timeStep);
	virtual void MakeGizmo();

	// Getters
	AABB GetAABB() { return m_boundBox; }

protected:

	AABB m_boundBox;

	// x(length) y(height)
	glm::vec2 m_size;
	glm::vec4 m_colour;

};

