#include "Sphere.h"

Sphere::Sphere(glm::vec2 position, glm::vec2 velocity, float mass, float radius, glm::vec4 colour, float angularDrag, float linearDrag) {
	m_shape = ShapeType::SPHERE;

	m_position	= position;
	m_velocity	= velocity;
	m_mass		= mass;
	m_radius	= radius;
	m_colour	= colour;

	m_angularDrag	= angularDrag;
	m_linearDrag	= linearDrag;
}

Sphere::~Sphere() {
}

void Sphere::MakeGizmo() {
	Gizmos::add2DCircle(m_position, m_radius, 18, m_colour);
}
