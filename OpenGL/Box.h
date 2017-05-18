#pragma once
#include "Rigidbody.h"
#include "AIE\Gizmos.h"

class Box : public Rigidbody {
public:
	Box();
	Box(glm::vec2 position, float length, float height, float mass, glm::vec4 colour = glm::vec4(1));
	~Box();

	virtual void MakeGizmo();

protected:

	// Box AABB here

	// x(length) y(height)
	glm::vec2 m_size;
	glm::vec4 m_colour;

};

