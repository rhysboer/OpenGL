#pragma once
#include "PhysicsObject.h"
#include "Time.h"
#include "imgui.h"
#include <string>

#define MIN_LINEAR_THRESHOLD 0.1f
#define MIN_ROTATION_THRESHOLD 0.01f

class Rigidbody : public PhysicsObject {
public:
	Rigidbody();
	Rigidbody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float rotation, float mass, float lineaerDrag = 1, float angularDrag = 1);
	~Rigidbody();

	virtual void FixedUpdate(glm::vec2 gravity, float timeStep);
	virtual void Debug(int id);

	// Physics
	void ApplyTorque(float torque);
	void ApplyForce(glm::vec2 force);
	void ApplyForceToActor(Rigidbody* actor2, glm::vec2 force);

	// Get Functions
	glm::vec2 GetPosition() const { return m_position; }
	glm::vec2 GetVelocity() const { return m_velocity; }
	float GetRotation() const { return m_rotation; }
	float GetMass() const { return m_mass; }
	float GetElasticity() const { return m_elasticity; }
	bool IsStatic() const { return m_isStatic; }

	// Set Functions
	void SetVelocity(const glm::vec2 velocity) { m_velocity = velocity; }
	void SetPosition(const glm::vec2 position) { if(m_isStatic == false) m_position = position; }
	void SetElasticity(const float elasticity) { m_elasticity = elasticity; }
	void SetStatic(const bool isStatic) { m_isStatic = isStatic; }

protected:
	glm::vec2 GetMomentum();

	glm::vec2 m_position;
	glm::vec2 m_velocity;

	bool m_isStatic;

	float m_angularVelocity;

	float m_mass;
	float m_rotation;
	float m_elasticity;

	float m_linearDrag;
	float m_angularDrag;

};

