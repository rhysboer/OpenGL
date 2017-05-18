#include "Sphere.h"

Sphere::Sphere(glm::vec2 position, glm::vec2 velocity, float mass, float radius, glm::vec4 colour) {
	m_shape = ShapeType::SPHERE;

	m_position	= position;
	m_velocity	= velocity;
	m_mass		= mass;
	m_radius	= radius;
	m_colour	= colour;
}

Sphere::~Sphere() {
}

void Sphere::MakeGizmo() {
	Gizmos::add2DCircle(m_position, m_radius, 12, m_colour);
}
