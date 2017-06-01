#pragma once
#include "PhysicsObject.h"
#include "Time.h"

// DELETE
#include "imgui.h"
#include <string>

class Rigidbody : public PhysicsObject {
public:
	Rigidbody() {};
	Rigidbody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float rotation, float mass);
	~Rigidbody();

	virtual void FixedUpdate(glm::vec2 gravity, float timeStep);
	virtual void Debug(int id);

	void ApplyForce(glm::vec2 force);
	void ApplyForceToActor(Rigidbody* actor2, glm::vec2 force);

	// Get Functions
	glm::vec2 GetPosition() { return m_position; }
	glm::vec2 GetVelocity() { return m_velocity; }
	float GetRotation() { return m_rotation; }
	float GetMass() { return m_mass; }

	// Set Functions
	void SetVelocity(const glm::vec2 velocity) { m_velocity = velocity; }
	void SetPosition(const glm::vec2 position) { m_position = position; }

protected:
	glm::vec2 GetMomentum();


	glm::vec2 m_position;
	glm::vec2 m_velocity;

	float m_mass;
	float m_rotation;
};

