#include "RigidBody.h"



RigidBody::RigidBody()
{
	RigidBody::mass = 0;
	RigidBody::inertia = btVector3(0,0,0);
}


RigidBody::~RigidBody()
{
}

void RigidBody::init()
{
	btRigidBody::btRigidBodyConstructionInfo
		constructionInfo(RigidBody::mass, RigidBody::state, RigidBody::collider, RigidBody::inertia);

	RigidBody::rigidbody = new btRigidBody(constructionInfo);
}

void RigidBody::addCollider(btCollisionShape * collider){
	RigidBody::collider = collider;
}

void RigidBody::addMotionState(btMotionState * state)
{
	RigidBody::state = state;
}

void RigidBody::setMass(float mass)
{
	RigidBody::mass = mass;
}

void RigidBody::calculateLocalInertia()
{
	collider->calculateLocalInertia(btScalar(RigidBody::mass), RigidBody::inertia);
	printf("Inertia X Loc: %f, Y Loc: %f, Z Loc: %f\n", inertia.getX(), inertia.getY(), inertia.getZ());
}

void RigidBody::addForce()
{
}

vec3 RigidBody::getMotionState()
{
	btTransform btTrans;
	rigidbody->getMotionState()->getWorldTransform(btTrans);
	printf(" Y Loc: %f\n", btTrans.getOrigin().getY());
	return vec3(btTrans.getOrigin().getX(), btTrans.getOrigin().getY(), btTrans.getOrigin().getZ());
}

void RigidBody::destroy()
{
	delete collider;
	delete rigidbody;
	delete this;
}
