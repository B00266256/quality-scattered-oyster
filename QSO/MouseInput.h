#pragma once

#include <glm\glm.hpp>

using namespace glm;

class MouseInput
{
private:
	vec2 position;
	vec2 lastPosition;
	vec2 offSet;
	vec2 scrollOffset;
	vec2 lastScrollOffset;
public:
	MouseInput();
	~MouseInput();

	void setPosition(vec2 position);
	void setLastPosition(vec2 position);
	vec2 getPosition();
	vec2 getLastPosition();
	void setOffset(vec2 offSet);
	vec2 getOffset();
	void setScrollOffset(vec2 offSet);
	void setLastScrollOffset(vec2 scrollOffset);
	vec2 getScrollOffset();
	vec2 getLastScrollOffset();

};

