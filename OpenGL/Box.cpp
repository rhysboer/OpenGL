#include "Box.h"

Box::Box() {
	m_shape = ShapeType::BOX;
}

Box::Box(glm::vec2 position, float length, float height, float mass, glm::vec4 colour) {
	m_shape = ShapeType::BOX;

	m_size = glm::vec2(length, height);
	m_position = position;
	m_mass = mass;
	m_colour = colour;
}

Box::~Box() {
}

void Box::MakeGizmo() {
	Gizmos::add2DAABBFilled(m_position, m_size, m_colour);
}
