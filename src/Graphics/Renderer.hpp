#ifndef AG_RENDERER_H
#define AG_RENDERER_H

class Drawable;
#include "Vector2.hpp"
#include <entt/entity/registry.hpp>

#define PIXELS_PER_METER 100

class Renderer {
	public:
	virtual void Initialize() = 0;
	virtual void StartRender() = 0;
	virtual void Draw(entt::registry& reg) = 0;
	virtual void EndRender() = 0;
	virtual void Quit() = 0;
	virtual bool IsOpen() = 0;

	virtual Vector2f GetTextureSize(uint id) const = 0;

	static std::unique_ptr<Renderer> CreateBestRenderer();
};

#endif