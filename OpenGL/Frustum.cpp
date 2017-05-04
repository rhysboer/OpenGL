#include "Frustum.h"



Frustum::Frustum() {
}


Frustum::~Frustum() {
}

void Frustum::GetFrustumPlanes(const mat4 & transform, vec4 * planes) {
	// right side
	planes[0] = vec4(transform[0][3] - transform[0][0],
		transform[1][3] - transform[1][0],
		transform[2][3] - transform[2][0],
		transform[3][3] - transform[3][0]);

	// left side
	planes[1] = vec4(transform[0][3] + transform[0][0],
		transform[1][3] + transform[1][0],
		transform[2][3] + transform[2][0],
		transform[3][3] + transform[3][0]);

	// top
	planes[2] = vec4(transform[0][3] - transform[0][1],
		transform[1][3] - transform[1][1],
		transform[2][3] - transform[2][1],
		transform[3][3] - transform[3][1]);

	// bottom
	planes[3] = vec4(transform[0][3] + transform[0][1],
		transform[1][3] + transform[1][1],
		transform[2][3] + transform[2][1],
		transform[3][3] + transform[3][1]);

	// far
	planes[4] = vec4(transform[0][3] - transform[0][2],
		transform[1][3] - transform[1][2],
		transform[2][3] - transform[2][2],
		transform[3][3] - transform[3][2]);
	
	// near
	planes[5] = vec4(transform[0][3] + transform[0][2],
		transform[1][3] + transform[1][2],
		transform[2][3] + transform[2][2],
		transform[3][3] + transform[3][2]);

	// plane normalisation, based on length of normal
	for(int i = 0; i < 6; i++) {
		float d = glm::length(glm::vec3(planes[i]));
		planes[i] /= d;
	}
}
