#include "Box.h"

Box::Box() {
	m_shape = ShapeType::AABB;

	m_size = glm::vec2(1);
	m_position = glm::vec2(0);
	m_mass = 1;
	m_colour = glm::vec4(1);

	m_boundBox.Fit(glm::vec2(0), glm::vec2(0), glm::vec2(0), glm::vec2(0));
}

Box::Box(glm::vec2 position, float length, float height, float mass, glm::vec4 colour) {
	m_shape = ShapeType::AABB;

	m_size = glm::vec2(length, height);
	m_position = position;
	m_mass = mass;
	m_colour = colour;

	m_boundBox.Fit(
		glm::vec2(position.x - length, position.y + height), // Top Left
		glm::vec2(position.x + length, position.y + height), // Top Right
		glm::vec2(position.x - length, position.y - height), // Bottom Left
		glm::vec2(position.x + length, position.y - height)	 // Bottom Right
	); 
}

Box::~Box() {
}

void Box::FixedUpdate(glm::vec2 gravity, float timeStep) {
	Rigidbody::FixedUpdate(gravity, timeStep);
	
	m_boundBox.Fit(
		glm::vec2(m_position.x - m_size.x, m_position.y + m_size.y), // Top Left
		glm::vec2(m_position.x + m_size.x, m_position.y + m_size.y), // Top Right
		glm::vec2(m_position.x - m_size.x, m_position.y - m_size.y), // Bottom Left
		glm::vec2(m_position.x + m_size.x, m_position.y - m_size.y)	 // Bottom Right
	);
}

void Box::MakeGizmo() {
	Gizmos::add2DAABBFilled(m_position, m_size, m_colour);

	// Debug Draw AABB
	/*
	glm::vec2 topLeft = glm::vec2(m_boundBox.GetMin().x, m_boundBox.GetMax().y);
	glm::vec2 topRight = glm::vec2(m_boundBox.GetMax().x, m_boundBox.GetMax().y);
	glm::vec2 botLeft = glm::vec2(m_boundBox.GetMin().x, m_boundBox.GetMin().y);
	glm::vec2 botRight = glm::vec2(m_boundBox.GetMax().x, m_boundBox.GetMin().y);
	
	Gizmos::add2DLine(topLeft, topRight, glm::vec4(1));
	Gizmos::add2DLine(topRight, botRight, glm::vec4(1));
	Gizmos::add2DLine(botRight, botLeft, glm::vec4(1));
	Gizmos::add2DLine(botLeft, topLeft, glm::vec4(1));
	*/
}
