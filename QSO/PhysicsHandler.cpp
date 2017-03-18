#include "PhysicsHandler.h"



PhysicsHandler::PhysicsHandler()
{
	_broadphase = new btDbvtBroadphase();
	_collisionConfiguration = new btDefaultCollisionConfiguration();
	_dispatcher = new btCollisionDispatcher(_collisionConfiguration);
	btGImpactCollisionAlgorithm::registerAlgorithm(_dispatcher);
	_solver = new btSequentialImpulseConstraintSolver;
	_dynamicsWorld = new btDiscreteDynamicsWorld(_dispatcher, _broadphase, _solver, _collisionConfiguration);
}


PhysicsHandler::~PhysicsHandler()
{
}

void PhysicsHandler::setGravity(vec3 gravity)
{
	gravity = gravity;
	_dynamicsWorld->setGravity(btVector3(gravity.x, gravity.y, gravity.z));
}

void PhysicsHandler::addRigidBody(RigidBody * body)
{
	_dynamicsWorld->addRigidBody(body->rigidbody);
}

void PhysicsHandler::stepSimulation(int deltaTime, int maxSubSteps)
{
	_dynamicsWorld->stepSimulation(deltaTime, maxSubSteps);
}

void PhysicsHandler::destroy()
{
	delete _broadphase;
	delete _collisionConfiguration;
	delete _dispatcher;
	delete _solver;
	delete _dynamicsWorld;
	delete this;
}
