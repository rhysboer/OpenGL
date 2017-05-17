#pragma once
#include "PhysicsObject.h"

// DELETE
#include "imgui.h"

class Rigidbody : public PhysicsObject {
public:
	Rigidbody() {};
	Rigidbody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float rotation, float mass);
	~Rigidbody();

	virtual void FixedUpdate(glm::vec2 gravity, float timeStep);
	virtual void Debug();

	void ApplyForce(glm::vec2 force);
	void ApplyForceToActor(Rigidbody* actor2, glm::vec2 force);

	// Get Functions
	glm::vec2 GetPosition() { return m_position; }
	glm::vec2 GetVelocity() { return m_velocity; }
	float GetRotation() { return m_rotation; }
	float GetMass() { return m_mass; }

protected:
	glm::vec2 GetMomentum();


	glm::vec2 m_position;
	glm::vec2 m_velocity;

	float m_mass;
	float m_rotation;
};

