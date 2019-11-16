#ifndef ENTITY_H
#define ENTITY_H

#include "Drawable.hpp"

class Entity : public Drawable {
	public:
	Entity() : Drawable(0) {}
};

#endif