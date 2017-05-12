#pragma once
#include <vector>
#include "PhysicsObject.h"
#include "AIE\Gizmos.h"

class PhysicsManager {
public:
	PhysicsManager();
	~PhysicsManager();

	void Update();
	void UpdateGizmos();
	void DebugScene();

	void Draw(glm::mat4 m_projection); // ???

	void AddActor(PhysicsObject* actor);
	void RemoveActor(PhysicsObject* actor);

	void SetGravity(const glm::vec2 gravity) { m_gravity = gravity; }
	void SetTimeStep(const float timeStep) { m_timeStep = timeStep; }
	
	float GetTimeStep() const { return m_timeStep; }
	glm::vec2 GetGravity() const { return m_gravity; }

private:

	glm::vec2 m_gravity = glm::vec2(0, -9.81f);
	float m_timeStep;

	std::vector<PhysicsObject*> m_actors;
};

