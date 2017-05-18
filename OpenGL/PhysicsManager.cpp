#include "PhysicsManager.h"
#include "Sphere.h"
#include "Plane.h"

PhysicsManager::PhysicsManager() {
}

PhysicsManager::~PhysicsManager() {
}

void PhysicsManager::Update(float dt) {
	int i = 0;
	for(auto iter = m_actors.begin(); iter != m_actors.end(); ++iter) {
		(*iter)->FixedUpdate(m_gravity, i);
		++i;
	}

	CheckForCollisions();
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

static fn CollisionFunctionArray[] = 
{
	PhysicsManager::Plane2Plane,	PhysicsManager::Plane2Sphere,	PhysicsManager::Plane2Box,
	PhysicsManager::Sphere2Plane,	PhysicsManager::Sphere2Sphere,	PhysicsManager::Sphere2Box,
	PhysicsManager::Box2Plane,		PhysicsManager::Box2Sphere,		PhysicsManager::Box2Box,
};

// -------------------- //
//		Collisons		//
// -------------------- //

void PhysicsManager::CheckForCollisions() {
	int size = m_actors.size();

	for(int outer = 0; outer < size - 1; outer++) {
		for(int inner = outer + 1; inner < size; inner++) {
			PhysicsObject* obj1 = m_actors[outer];
			PhysicsObject* obj2 = m_actors[inner];
			int shape1 = (int)obj1->GetShapeID();
			int shape2 = (int)obj2->GetShapeID();

			int index = (shape1 * (int)ShapeType::SHAPE_COUNT) + shape2 - 1;

			fn functionPtr = CollisionFunctionArray[index];

			if(functionPtr != nullptr) {
				functionPtr(obj1, obj2);
			}
		}
	}
}

bool PhysicsManager::Sphere2Plane(PhysicsObject *obj1, PhysicsObject *obj2) {
	Sphere* sphere = dynamic_cast<Sphere*>(obj1);
	Plane* plane = dynamic_cast<Plane*>(obj2);

	if(sphere != nullptr && plane != nullptr) {
		glm::vec2 collisionNormal = plane->GetNormal();
		float sphereToPlane = glm::dot(sphere->GetPosition(), plane->GetNormal()) - plane->GetDistance();

		if(sphereToPlane < 0) {
			collisionNormal *= -1;
			sphereToPlane *= -1;
		}

		float intersection = sphere->GetRadius() - sphereToPlane;
		if(intersection > 0) {
			/* COLLISION */
			sphere->SetVelocity(glm::vec2(0));

			return true;
		}

	}

	return false;
}

bool PhysicsManager::Sphere2Sphere(PhysicsObject * obj1, PhysicsObject *obj2) {
	Sphere* sphere1 = dynamic_cast<Sphere*>(obj1);
	Sphere* sphere2 = dynamic_cast<Sphere*>(obj2);

	if(sphere1 != nullptr && sphere2 != nullptr) {
		if((glm::distance(sphere1->GetPosition(), sphere2->GetPosition())) < (sphere1->GetRadius() + sphere2->GetRadius())) {
			/* COLLISION */

			sphere1->SetVelocity(glm::vec2(0));
			sphere2->SetVelocity(glm::vec2(0));

			return true;
		}
	}

	return false;
}
