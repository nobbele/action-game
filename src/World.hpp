#ifndef AG_WORLD_H
#define AG_WORLD_H

#include "Entity.hpp"
#include <Box2D/Box2D.h>

class World {
public:
	inline World(b2Vec2 grav) : PhysicsWorld(grav) {}

	b2World PhysicsWorld;
};

#endif