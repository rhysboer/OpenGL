#include "PhysicsManager.h"

PhysicsManager::PhysicsManager() {
}

PhysicsManager::~PhysicsManager() {
}

void PhysicsManager::Update(float dt) {
	for(auto iter = m_actors.begin(); iter != m_actors.end(); ++iter) {
		(*iter)->FixedUpdate(m_gravity, dt);
	}
}

void PhysicsManager::UpdateGizmos() {
	for(auto iter = m_actors.begin(); iter != m_actors.end(); ++iter) {
		(*iter)->MakeGizmo();
	}
}

void PhysicsManager::DebugScene() {
	for(auto iter = m_actors.begin(); iter != m_actors.end(); ++iter) {
		(*iter)->Debug();
	}
}

void PhysicsManager::Draw(glm::mat4 m_projection) {
	Gizmos::draw2D(m_projection);
}

void PhysicsManager::AddActor(PhysicsObject * actor) {
	m_actors.push_back(actor);
}

void PhysicsManager::RemoveActor(PhysicsObject * actor) {
	auto iter = std::find(m_actors.begin(), m_actors.end(), actor);
	if(iter != m_actors.end())
		m_actors.erase(iter);
}
