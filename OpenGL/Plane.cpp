#include "Plane.h"

//Plane::Plane() {
//}

Plane::Plane(glm::vec2 normal, float height, float rotation) {
	m_shape = ShapeType::PLANE;

	if(rotation != 0.0f)
		m_normal = glm::rotate(normal, glm::radians(rotation));
	else
		m_normal = normal;

	m_distanceToOrigin = height;
}


Plane::~Plane() {
}

void Plane::FixedUpdate(glm::vec2 gravity, float timeStep) {
}

void Plane::MakeGizmo() {
	float lineSegmentLength = 100;
	
	glm::vec2 centerPoint = m_normal * m_distanceToOrigin;

	glm::vec2 parallel(m_normal.y, -m_normal.x);
	glm::vec4 colour = Colours::White;

	glm::vec2 start = centerPoint + (parallel * lineSegmentLength);
	glm::vec2 end = centerPoint - (parallel * lineSegmentLength);

	// Line
	Gizmos::add2DLine(start, end, colour);
	// Normal
	Gizmos::add2DLine(centerPoint, centerPoint + glm::normalize(m_normal), Colours::Red);
}
