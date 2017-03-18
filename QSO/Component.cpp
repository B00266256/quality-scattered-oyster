#include "Component.h"
#include "GameObject.h"
#include "Transform.h"


Component::Component()
{
}

Component::Component(std::string name)
{
	Object::name = name;
}


Component::~Component()
{
}
