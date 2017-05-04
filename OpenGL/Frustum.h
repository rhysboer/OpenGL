#pragma once
#include "glm.hpp"
#include "GLM\vec4.hpp"
#include "GLM\mat4x4.hpp"

using glm::mat4;
using glm::vec4;

class Frustum {
public:
	Frustum();
	~Frustum();

	void GetFrustumPlanes(const mat4& transform, vec4* planes);

private:

};

