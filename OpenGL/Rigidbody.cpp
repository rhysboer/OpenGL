#include "Rigidbody.h"

Rigidbody::Rigidbody() {
	m_angularDrag = 1;
	m_linearDrag = 1;
	m_elasticity = 1;

	m_isStatic = false;
}

Rigidbody::Rigidbody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float rotation, float mass, float lineaerDrag, float angularDrag) {
	m_shape		= shapeID;
	m_position	= position;
	m_velocity	= velocity;
	m_rotation	= rotation;
	m_mass		= mass;

	m_angularDrag	= lineaerDrag;
	m_linearDrag	= angularDrag;
	m_elasticity	= 1;

	m_isStatic = false;
}

Rigidbody::~Rigidbody() {
}

void Rigidbody::FixedUpdate(glm::vec2 gravity, float timeStep) {
	if(m_isStatic == true) return;

	ApplyForce(gravity * m_mass * Time::DeltaTime());
	m_position += m_velocity * Time::DeltaTime();
	m_velocity *= m_linearDrag; // do delta time
	m_angularVelocity -= m_angularVelocity * m_angularDrag * Time::DeltaTime();
	m_rotation += m_angularVelocity * Time::DeltaTime();

	if(glm::length(m_velocity) < MIN_LINEAR_THRESHOLD)
		m_velocity = glm::vec2(0);

	if(glm::length(m_angularDrag) < MIN_ROTATION_THRESHOLD)
		m_angularVelocity = 0;
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

void Rigidbody::ApplyTorque(float torque) {
	m_angularVelocity += torque / m_mass;
}

void Rigidbody::ApplyForce(glm::vec2 force) {
	if(m_isStatic == true) return;

	m_velocity += force / m_mass; 
}

void Rigidbody::ApplyForceToActor(Rigidbody * actor2, glm::vec2 force) {
	this->ApplyForce(-force);
	actor2->ApplyForce(force);
}

glm::vec2 Rigidbody::GetMomentum() {
	return m_mass * m_velocity;
}
