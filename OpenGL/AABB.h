#pragma once
#include <vector>
#include "glm.hpp"

#define MAX 1e37f
#define MIN -1e37f

using glm::vec2;
using glm::vec3;

struct Points2D {
	vec2 topRight, topLeft;
	vec2 botRight, botLeft;
};

class AABB {
public:
	AABB();
	AABB(vec2 p1, vec2 p2, vec2 p3, vec2 p4);
	AABB(vec3 p1, vec3 p2, vec3 p3, vec3 p4);
	~AABB();

	void Reset();
	void Fit(const std::vector<vec3>& points);
	void Fit(vec2 p1, vec2 p2, vec2 p3, vec2 p4);
	void Fit(vec3 p1, vec3 p2, vec3 p3, vec3 p4);

	vec3 GetMax() { return m_max; }
	vec3 GetMin() { return m_min; }

	bool IsOverlapping(const AABB& box);
	static bool IsOverlapping(const AABB& box1, const AABB& box2);

	bool IsPointInside(const vec2 point);
	bool IsPointInside(const vec3 point);

	Points2D GetPoints2D();
private:

	vec3 m_min, m_max;
};

