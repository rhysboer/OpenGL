#pragma once
#include <vector>
#include "glm.hpp"
#include "GLM\vec3.hpp"

#define MIN -1e37f
#define MAX 1e37f

using glm::vec3;
using glm::vec2;

class BoundingSphere {
public:
	BoundingSphere() : centre(0), radius(0) {}
	BoundingSphere(vec3 sphereCentre, float sphereRadius) {
		centre = sphereCentre;
		radius = sphereRadius;
	}

	BoundingSphere(vec2 sphereCentre, float sphereRadius) {
		centre = vec3(sphereCentre,0);
		radius = sphereRadius;
	}

	~BoundingSphere() {}

	void Fit(const std::vector<vec3>& points) {
		vec3 min(MAX), max(MIN);

		for(auto& p : points) {
			if(p.x < min.x) min.x = p.x;
			if(p.y < min.y) min.y = p.y;
			if(p.z < min.z) min.z = p.z;

			if(p.x > max.x) max.x = p.x;
			if(p.y > max.y) max.y = p.y;
			if(p.z > max.z) max.z = p.z;
		}

		centre = (min + max) * 0.5f;
		radius = glm::distance(min, centre);
	}

	bool IsPointInside(const vec3 point) {
		if(glm::distance(point, centre) < radius)
			return true;

		return false;
	}

	bool IsPointInside(const vec2 point) {
		return IsPointInside(vec3(point, 0));
	}

	vec3 centre = vec3(0);
	float radius = 0.0f;
};

