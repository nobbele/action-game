#ifndef AG_ENTITY_H
#define AG_ENTITY_H

#include "Graphics/Drawable.hpp"
#include <Box2D/Box2D.h>

class World;

class Entity : public Drawable {
	public:
	inline Vector2f GetPosition() const {
		Vector2f pos = Body->GetPosition();
		return pos * PIXELS_PER_METER;
	}

	inline void SetPosition(Vector2f vec) {
		Body->SetTransform(vec / PIXELS_PER_METER, Body->GetAngle());
	}

	b2FixtureDef FixtureDef;
	b2Body* Body;
};

#endif