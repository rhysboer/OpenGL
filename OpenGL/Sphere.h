#pragma once
#include "Rigidbody.h"

class Sphere : public Rigidbody {
public:
	Sphere(glm::vec2 position, glm::vec2 velocity, float mass, float radius, glm::vec4 colour);
	~Sphere();

	virtual void MakeGizmo();

	float GetRadius() { return m_radius; }
	glm::vec4 GetColour() { return m_colour; }

protected:
	float m_radius;
	glm::vec4 m_colour;
};

