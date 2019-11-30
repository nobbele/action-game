#ifndef AG_WORLD_H
#define AG_WORLD_H

class Entity;
#include <Box2D/Box2D.h>

class World {
public:
	inline World(b2Vec2 grav) : PhysicsWorld(grav) {}
	std::vector<Entity> Entities;
	b2World PhysicsWorld;
};

#endif