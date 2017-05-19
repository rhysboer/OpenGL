#include "Plane.h"

Plane::Plane() {
}

Plane::Plane(glm::vec2 normal, float distance) {
	m_shape = ShapeType::PLANE;

	m_normal = normal;
	m_distanceToOrigin = distance;
}

Plane::~Plane() {
}

void Plane::FixedUpdate(glm::vec2 gravity, float timeStep) {
}

void Plane::MakeGizmo() {
	float lineSegmentLength = 300;
	
	glm::vec2 centerPoint = m_normal * m_distanceToOrigin;
	glm::vec2 parallel(m_normal.y, -m_normal.x);
	glm::vec4 colour = Colours::White;
	glm::vec2 start = centerPoint + (parallel * lineSegmentLength);
	glm::vec2 end = centerPoint - (parallel * lineSegmentLength);

	Gizmos::add2DLine(start, end, colour);
}
