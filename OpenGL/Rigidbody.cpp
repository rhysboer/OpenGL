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
	// GUI
	{
		glm::vec2 grav = gravity * timeStep;
		ImGui::Begin("Physics Object");
		ImGui::DragFloat("Delta Time", &timeStep);
		ImGui::DragFloat2("Gravity", &grav[0]);
		ImGui::DragFloat3("Position", &m_position[0]);
		ImGui::DragFloat3("Velocity", &m_velocity[0]);
		ImGui::End();
	}
	// END GUI

	m_velocity += gravity * timeStep;
	m_velocity = GetMomentum();

	m_position += m_velocity;
}

void Rigidbody::Debug() {
}

void Rigidbody::ApplyForce(glm::vec2 force) {
	m_velocity = force / m_mass; //?
}

void Rigidbody::ApplyForceToActor(Rigidbody * actor2, glm::vec2 force) {
	this->ApplyForce(-force);
	actor2->ApplyForce(force);
}

glm::vec2 Rigidbody::GetMomentum() {
	return m_mass * m_velocity;
}
