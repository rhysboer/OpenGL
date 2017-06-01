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
	m_position += m_velocity * Time::DeltaTime();

	ApplyForce(gravity);
}

void Rigidbody::Debug(int id) {
	{ // GUI
		std::string str = std::string("Physic Object ");
		str += std::to_string(id);

		ImGui::Begin(str.c_str());
		ImGui::Text("Object");
		ImGui::DragFloat2("Position", &m_position[0]);
		ImGui::DragFloat2("Velocity", &m_velocity[0]);
		ImGui::DragFloat2("Momentum", &GetMomentum()[0]);
		ImGui::DragFloat("Mass", &m_mass);
		ImGui::End();
	} // END GUI
}

void Rigidbody::ApplyForce(glm::vec2 force) {
	m_velocity += force / m_mass; //?
}

void Rigidbody::ApplyForceToActor(Rigidbody * actor2, glm::vec2 force) {
	this->ApplyForce(-force);
	actor2->ApplyForce(force);
}

glm::vec2 Rigidbody::GetMomentum() {
	return m_mass * m_velocity;
}
