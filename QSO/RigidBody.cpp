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
		constructionInfo(0, RigidBody::state, RigidBody::collider, RigidBody::inertia);
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
	collider->calculateLocalInertia(RigidBody::mass, RigidBody::inertia);
}

vec3 RigidBody::getMotionState()
{
	btTransform btTrans;
	rigidbody->getMotionState()->getWorldTransform(btTrans);
	return vec3(btTrans.getOrigin().getX(), btTrans.getOrigin().getY(), btTrans.getOrigin().getZ());
}

void RigidBody::destroy()
{
	delete collider;
	delete rigidbody;
	delete this;
}
