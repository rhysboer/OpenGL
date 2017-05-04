#include "AABB.h"



AABB::AABB() {
}


AABB::~AABB() {
}

void AABB::Reset() {
	min.x = min.y = min.z = MAX;
	max.x = max.y = max.z = MIN;
}

void AABB::Fit(const std::vector<vec3>& points) {
	for(auto& p : points) {
		if(p.x < min.x) min.x = p.x;
		if(p.y < min.y) min.y = p.y;
		if(p.z < min.z) min.z = p.z;
		
		if(p.x > max.x) max.x = p.x;
		if(p.y > max.y) max.y = p.y;
		if(p.z > max.z) max.z = p.z;
	}
}
