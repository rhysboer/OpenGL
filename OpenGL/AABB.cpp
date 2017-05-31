#include "AABB.h"

AABB::AABB() {
	Reset();
}

AABB::AABB(vec2 p1, vec2 p2, vec2 p3, vec2 p4) {
	Reset();
	Fit(p1, p2, p3, p4);
}

AABB::AABB(vec3 p1, vec3 p2, vec3 p3, vec3 p4) {
	Reset();
	Fit(p1, p2, p3, p4);
}

AABB::~AABB() {
}

void AABB::Reset() {
	m_min.x = m_min.y = m_min.z = MAX;
	m_max.x = m_max.y = m_max.z = MIN;
}

void AABB::Fit(const std::vector<vec3>& points) {
	Reset();

	for(auto& p : points) {
		if(p.x < m_min.x) m_min.x = p.x;
		if(p.y < m_min.y) m_min.y = p.y;
		if(p.z < m_min.z) m_min.z = p.z;
		
		if(p.x > m_max.x) m_max.x = p.x;
		if(p.y > m_max.y) m_max.y = p.y;
		if(p.z > m_max.z) m_max.z = p.z;
	}
}

void AABB::Fit(vec2 p1, vec2 p2, vec2 p3, vec2 p4) {
	Fit(vec3(p1,0), vec3(p2,0), vec3(p3,0), vec3(p4,0));
}

void AABB::Fit(vec3 p1, vec3 p2, vec3 p3, vec3 p4) {
	std::vector<vec3> points;

	points.push_back(p1);
	points.push_back(p2);
	points.push_back(p3);
	points.push_back(p4);

	Fit(points);
}


/*
  max y		  max y
  min x	      max x
	_____________
	|			|
	|			|
	|			|
	|			|
	|___________|
  min y		  min y
  min x       max x
*/

bool AABB::IsOverlapping(const AABB & box) {
	return IsOverlapping(*this, box);
}

bool AABB::IsOverlapping(const AABB & box1, const AABB & box2) {
	if(box1.m_min.x <= box2.m_max.x && box1.m_max.x >= box2.m_min.x && box1.m_min.y <= box2.m_max.y &&
		box1.m_max.y >= box2.m_min.y && box1.m_min.z <= box2.m_max.z && box1.m_max.z >= box2.m_min.z) { 
		return true;
	}

	return false;
}

bool AABB::IsPointInside(const vec2 point) {
	if(point.x > m_min.x && point.x < m_max.x && point.y > m_min.y && point.y < m_max.y)
		return true;

	return false;
}

bool AABB::IsPointInside(const vec3 point) {
	return IsPointInside(vec2(point));
}

Points2D AABB::GetPoints2D() {
	Points2D points;
	points.topRight = vec2(m_max.x, m_max.y); points.topLeft = vec2(m_min.x, m_max.y);
	points.botLeft = vec2(m_min.x, m_min.y); points.botRight = vec2(m_max.x, m_min.y);
	return points;
}
