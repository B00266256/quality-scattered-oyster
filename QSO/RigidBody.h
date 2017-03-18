#pragma once
#include "Component.h"
#include "Collider.h"
#include "btBulletDynamicsCommon.h"
class RigidBody : public Component
{
private:
	btCollisionShape *collider;
	btMotionState *state;
	btScalar mass;
	btVector3 inertia;
	btTransform transform;
public:
	RigidBody();
	~RigidBody();
	void init();
	void addCollider(btCollisionShape *collider);
	void addMotionState(btMotionState *state);
	void setMass(float mass);
	void calculateLocalInertia();
	void addForce();
	vec3 getMotionState();
	void destroy();

	btRigidBody *rigidbody;
};

