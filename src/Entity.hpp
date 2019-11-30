#ifndef AG_ENTITY_H
#define AG_ENTITY_H

#include "Graphics/Drawable.hpp"
class World;
#include <Box2D/Box2D.h>

class Entity : public Drawable {
	public:
	Entity(World& world);

	inline Vector2f GetPosition() {
		b2Vec2 pos = Body->GetPosition();
		return pos;
	}

	b2BodyDef BodyDef;
	b2PolygonShape DynamicBox;
	b2FixtureDef FixtureDef;
	b2Body* Body;
};

#endif