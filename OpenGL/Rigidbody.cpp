#include "Rigidbody.h"

Rigidbody::Rigidbody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float rotation, float mass) {
	m_shape		= shapeID;
	m_position	= position;
	m_velocity	= velocity;
	m_rotation	= rotation;
	m_mass		= mass;
}

Rigidbody::~Rigidbody() {
}

void Rigidbody::FixedUpdate(glm::vec2 gravity, float timeStep) {
	m_velocity += gravity * timeStep;

	m_position += m_velocity;
}

void Rigidbody::Debug() {
}

void Rigidbody::ApplyForce(glm::vec2 force) {
	m_velocity = force / m_mass; //?
}

glm::vec2 Rigidbody::GetMomentum() {
	return m_mass * m_velocity;
}
