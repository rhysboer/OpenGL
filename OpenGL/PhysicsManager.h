#pragma once
#include <vector>
#include "PhysicsObject.h"
#include "AIE\Gizmos.h"
#include "glm.hpp"
#include "Time.h"
#include "BoundingSphere.h"

typedef bool(*fn)(PhysicsObject*, PhysicsObject*);

class Sphere;
class Plane;
class Box;

class PhysicsManager {
public:
	PhysicsManager();
	~PhysicsManager();

	void Update(float dt);
	void UpdateGizmos();
	void DebugScene();

	void Draw(glm::mat4 m_projection); // ???

	// Actor Management
	void AddActor(PhysicsObject* actor);
	void RemoveActor(PhysicsObject* actor);

	void SetGravity(const glm::vec2 gravity) { m_gravity = gravity; }
	void SetTimeStep(const float timeStep) { m_timeStep = timeStep; }
	
	float GetTimeStep() const { return m_timeStep; }
	glm::vec2 GetGravity() const { return m_gravity; }

	// Collision Functions
	void CheckForCollisions();

	static bool Plane2Plane(PhysicsObject*, PhysicsObject*)	 {return false;};
	static bool Plane2Sphere(PhysicsObject*, PhysicsObject*);
	static bool Plane2Box(PhysicsObject*, PhysicsObject*);

	static bool Sphere2Plane(PhysicsObject*, PhysicsObject*);
	static bool Sphere2Sphere(PhysicsObject*, PhysicsObject*);
	static bool Sphere2Box(PhysicsObject*, PhysicsObject*);

	static bool Box2Plane(PhysicsObject*, PhysicsObject*);
	static bool Box2Sphere(PhysicsObject*, PhysicsObject*);
	static bool Box2Box(PhysicsObject*, PhysicsObject*);

private:

	glm::vec2 m_gravity = glm::vec2(0, 0); // -9.81f
	double m_timeStep = 0;
	double m_currTime = 0;

	std::vector<PhysicsObject*> m_actors;
};

