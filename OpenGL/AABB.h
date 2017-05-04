#pragma once
#include <vector>
#include "GLM\vec3.hpp"

#define MAX 1e37f
#define MIN -1e37f

using glm::vec3;

class AABB {
public:
	AABB();
	~AABB();

	void Reset();
	void Fit(const std::vector<vec3>& points);

private:

	vec3 min, max;
};

