#include "PhysicsManager.h"
#include "Sphere.h"
#include "Plane.h"
#include "Box.h"

PhysicsManager::PhysicsManager() {
}

PhysicsManager::~PhysicsManager() {
}

void PhysicsManager::Update(float dt) {
	m_currTime += Time::DeltaTime();
	if(m_currTime > m_timeStep) {
		for(auto iter = m_actors.begin(); iter != m_actors.end(); ++iter) {
			(*iter)->FixedUpdate(m_gravity, 0);
		}

		m_currTime = 0;
	}

	CheckForCollisions();
}

void PhysicsManager::UpdateGizmos() {
	for(auto iter = m_actors.begin(); iter != m_actors.end(); ++iter) {
		(*iter)->MakeGizmo();
	}
}

void PhysicsManager::DebugScene() {
	int i = 0;
	for(auto iter = m_actors.begin(); iter != m_actors.end(); ++iter) {
		(*iter)->Debug(i);
		++i;
	}
}

void PhysicsManager::Draw(glm::mat4 m_projection) {
	Gizmos::draw2D(m_projection);
}

void PhysicsManager::GUI() {
	static vec2 m_spawnLocation = vec2(0, 5);
	static vec2 m_force = vec2(0);
	static vec4 m_colour = vec4(1,0,0,1);
	static vec2 m_size = vec2(1);
	static float m_mass = 1.0f;
	static float m_rotation = 0.0f;

	auto spawnCircle = [&]() {
		Sphere* sphere = new Sphere(m_spawnLocation, m_force, m_mass, m_size.x, m_colour);
		AddActor(sphere);
	};

	auto spawnBox = [&]() {
		Box* box = new Box(m_spawnLocation, m_size.x, m_size.y, m_mass, m_colour);
		AddActor(box);
	};

	auto spawnPlane = [&]() {
		Plane* plane = new Plane(m_spawnLocation, m_size.x, m_rotation);
		AddActor(plane);
	};

	ImGui::Begin("Physics Manager");
	ImGui::Text("Settings");
	ImGui::DragFloat2("Gravity", &m_gravity[0]);
	ImGui::DragFloat("Time Step", &m_timeStep, 0.01f, 0.0f, 60.0f);
	ImGui::Text("Spawning");
	ImGui::DragFloat2("Location", &m_spawnLocation[0]);
	ImGui::DragFloat2("Force", &m_force[0]);
	ImGui::DragFloat2("Size", &m_size[0]);
	ImGui::ColorEdit4("Colour", &m_colour[0]);
	ImGui::DragFloat("Rotation", &m_rotation);
	ImGui::DragFloat("Mass", &m_mass);

	if(ImGui::Button("Spawn Circle")) { spawnCircle(); }; ImGui::SameLine();
	//if(ImGui::Button("Spawn Box")) { spawnBox(); }; ImGui::SameLine();
	//if(ImGui::Button("Spawn Plane")) { spawnPlane(); };

	ImGui::End();
}

void PhysicsManager::AddActor(PhysicsObject * actor) {
	m_actors.push_back(actor);
}

void PhysicsManager::RemoveActor(PhysicsObject * actor) {
	auto iter = std::find(m_actors.begin(), m_actors.end(), actor);
	if(iter != m_actors.end())
		m_actors.erase(iter);
}

// -------------------- //
//		Collisons		//
// -------------------- //

static fn CollisionFunctionArray[] =
{
	PhysicsManager::Plane2Plane,	PhysicsManager::Plane2Sphere,	PhysicsManager::Plane2Box,
	PhysicsManager::Sphere2Plane,	PhysicsManager::Sphere2Sphere,	PhysicsManager::Sphere2Box,
	PhysicsManager::Box2Plane,		PhysicsManager::Box2Sphere,		PhysicsManager::Box2Box,
};

void PhysicsManager::CheckForCollisions() {
	int size = m_actors.size();

	for(int outer = 0; outer < size - 1; outer++) {
		for(int inner = outer + 1; inner < size; inner++) {
			PhysicsObject* obj1 = m_actors[outer];
			PhysicsObject* obj2 = m_actors[inner];
			int shape1 = (int)obj1->GetShapeID();
			int shape2 = (int)obj2->GetShapeID();

			int index = (shape1 * (int)ShapeType::SHAPE_COUNT) + shape2;

			fn functionPtr = CollisionFunctionArray[index];

			if(functionPtr != nullptr) {
				functionPtr(obj1, obj2);
			}
		}
	}
}

bool PhysicsManager::Plane2Sphere(PhysicsObject *obj1, PhysicsObject *obj2) {
	return Sphere2Plane(obj2, obj1);
}

bool PhysicsManager::Plane2Box(PhysicsObject *obj1, PhysicsObject *obj2) {
	return Box2Plane(obj2, obj1);
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

			glm::vec2 planeNormal = plane->GetNormal();
			if(sphereToPlane < 0) {
				planeNormal *= -1;
			}

			glm::vec2 forceVector = -1 * sphere->GetMass() * planeNormal * (glm::dot(planeNormal, sphere->GetVelocity()));

			float combinedElasticity = (sphere->GetElasticity() + 1.0f) / 2.0f;

			sphere->ApplyForce(forceVector+(forceVector*combinedElasticity)); // sphere->ApplyForce(2.0f * forceVector);
			sphere->SetPosition(sphere->GetPosition() + collisionNormal * intersection * 0.5f);

			return true;
		}
	}

	return false;
}

bool PhysicsManager::Sphere2Sphere(PhysicsObject * obj1, PhysicsObject *obj2) {
	Sphere* sphere1 = dynamic_cast<Sphere*>(obj1);
	Sphere* sphere2 = dynamic_cast<Sphere*>(obj2);

	if(sphere1 != nullptr && sphere2 != nullptr) {
		vec2 delta = sphere2->GetPosition() - sphere1->GetPosition();
		float distance = glm::length(delta);
		float intersection = sphere1->GetRadius() + sphere2->GetRadius() - distance;
		
		if(intersection > 0) {
			/* COLLISION */
		
			/* Vector perpendicular to the point of collision */
			vec2 collisionNormal = glm::normalize(delta);//(delta != vec2(0)) ? glm::normalize(delta) : vec2(0);
			/* The relative velocity of the two object colliding */
			vec2 relativeVelocity = sphere1->GetVelocity() - sphere2->GetVelocity();
			/* Collsion normal scaled by the dot product of the collision normal */
			vec2 collisionVector = collisionNormal * (glm::dot(relativeVelocity, collisionNormal));
			/* How much force get applied to the object */
			vec2 forceVector = collisionVector * 1.0f / (1.0f / sphere1->GetMass() + 1.0f / sphere2->GetMass());
		
			/* Combined both sphere elasticities */
			float combinedElasticity = (sphere1->GetElasticity() + sphere2->GetElasticity()) / 2.0f;
			sphere1->ApplyForceToActor(sphere2, forceVector+(forceVector*combinedElasticity));
		
		
			/* The vector along which will move the two objects so they are no longer colliding */
			vec2 separationVector = collisionNormal * intersection * 0.5f;
		
			if(sphere2->IsStatic()) {
				sphere1->SetPosition(sphere1->GetPosition() - (separationVector * 2.0f));

			} else {
				sphere1->SetPosition(sphere1->GetPosition() - separationVector);
				sphere2->SetPosition(sphere2->GetPosition() + separationVector);
			}
		
			return true;
		}
	}

	return false;
}

bool PhysicsManager::Sphere2Box(PhysicsObject *obj1, PhysicsObject *obj2) {
	Sphere* sphere = dynamic_cast<Sphere*>(obj1);
	Box* box = dynamic_cast<Box*>(obj2);

	if(sphere != nullptr && box != nullptr) {
		// Source: https://gamedev.stackexchange.com/questions/96337/collision-between-aabb-and-circle

		// Top Left | Top Right | Bot Left | Bot Right
		BoundingSphere cornerSphere[4];
		// Height Box | Width Box
		AABB boxes[2];

		// Set Spheres on all 4 corners
		cornerSphere[0] = BoundingSphere(box->GetAABB().GetPoints2D().topLeft, sphere->GetRadius());
		cornerSphere[1] = BoundingSphere(box->GetAABB().GetPoints2D().topRight, sphere->GetRadius());
		cornerSphere[2] = BoundingSphere(box->GetAABB().GetPoints2D().botLeft, sphere->GetRadius());
		cornerSphere[3] = BoundingSphere(box->GetAABB().GetPoints2D().botRight, sphere->GetRadius());

		// Height Box
		boxes[0] = AABB(box->GetAABB().GetPoints2D().topLeft + vec2(0, sphere->GetRadius()), box->GetAABB().GetPoints2D().topRight + vec2(0, sphere->GetRadius()),
			box->GetAABB().GetPoints2D().botLeft - vec2(0, sphere->GetRadius()), box->GetAABB().GetPoints2D().botRight - vec2(0, sphere->GetRadius()));

		// Width Box
		boxes[1] = AABB(box->GetAABB().GetPoints2D().topLeft - vec2(sphere->GetRadius(), 0), box->GetAABB().GetPoints2D().topRight + vec2(sphere->GetRadius(), 0),
			box->GetAABB().GetPoints2D().botLeft - vec2(sphere->GetRadius(), 0), box->GetAABB().GetPoints2D().botRight + vec2(sphere->GetRadius(), 0));

		// Check if sphere center is in Corner Spheres
		for(int i = 0; i < 4; i++) {
			if(cornerSphere[i].IsPointInside(sphere->GetPosition())) {
				/* COLLISION */
				box->SetVelocity(vec2(0));
				sphere->SetVelocity(vec2(0));
				return true;
			}
		}

		// Check if point is inside box
		for(int i = 0; i < 2; i++) {
			if(boxes[i].IsPointInside(sphere->GetPosition())) {
				/* COLLISION */
				box->SetVelocity(vec2(0));
				sphere->SetVelocity(vec2(0));
				return true;
			}
		}
	}

	return false;
}

bool PhysicsManager::Box2Plane(PhysicsObject *obj1, PhysicsObject *obj2) {
	Box* box = dynamic_cast<Box*>(obj1);
	Plane* plane = dynamic_cast<Plane*>(obj2);

	if(box != nullptr && plane != nullptr) {
		vec2 points[4] = { box->GetAABB().GetPoints2D().topRight, box->GetAABB().GetPoints2D().topLeft,
			box->GetAABB().GetPoints2D().botLeft, box->GetAABB().GetPoints2D().botRight }; // Set Points

		for(int i = 0; i < 4; i++) {
			// Source: https://gdbooks.gitbooks.io/3dcollisions/content/Chapter2/static_aabb_plane.html

			vec2 extents = (vec2)box->GetAABB().GetMax() - box->GetPosition();

			float radius = extents.x * glm::abs(plane->GetNormal().x) + extents.y * glm::abs(plane->GetNormal().y);
			float distance = glm::dot(plane->GetNormal(), box->GetPosition()) - plane->GetDistance();

			if(abs(distance) <= radius) {
				/* COLLISION */
				box->SetVelocity(vec2(0));

				return true;
			}
		}
	}

	return false;
}

bool PhysicsManager::Box2Sphere(PhysicsObject *obj1, PhysicsObject *obj2) {
	return Sphere2Box(obj2, obj1);
}

bool PhysicsManager::Box2Box(PhysicsObject *obj1, PhysicsObject *obj2) {
	Box* box1 = dynamic_cast<Box*>(obj1);
	Box* box2 = dynamic_cast<Box*>(obj2);
	
	if(box1 != nullptr && box2 != nullptr) {
		if(AABB::IsOverlapping(box1->GetAABB(), box2->GetAABB())) {
			/* COLLISION */

			box1->SetVelocity(glm::vec2(0));
			box2->SetVelocity(glm::vec2(0));

			return true;
		}
	}

	return false;
}
