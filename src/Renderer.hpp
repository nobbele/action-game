#ifndef RENDERER_H
#define RENDERER_H

#include "Drawable.hpp"

class Renderer {
	public:
	virtual void Initialize() = 0;
	virtual void Render(sf::RenderWindow& window, const Drawable& drawable) = 0;

	static std::unique_ptr<Renderer> CreateBestRenderer();
};

#endif