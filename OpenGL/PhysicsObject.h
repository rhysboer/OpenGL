#pragma once
#include "glm.hpp"

enum class ShapeType {
	PLANE = 0,
	SPHERE = 1,
	AABB = 2,

	SHAPE_COUNT // Always last
};

class PhysicsObject {
public:
	PhysicsObject() {};

	virtual void FixedUpdate(glm::vec2 gravity, float timeStep) = 0;
	virtual void Debug() = 0;
	virtual void MakeGizmo() = 0;
	virtual void ResetPosition() {};

	ShapeType GetShapeID() { return m_shape; }

protected:
	PhysicsObject(ShapeType a_shape) : m_shape(a_shape) {}
	ShapeType m_shape;
};

