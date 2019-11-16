#ifndef RENDERER_H
#define RENDERER_H

#include "Drawable.hpp"

class Renderer {
	public:
	virtual void Initialize() = 0;
	virtual void StartRender() = 0;
	virtual void Draw(const Drawable& drawable) = 0;
	virtual void EndRender() = 0;
	virtual void Quit() = 0;
	virtual bool IsOpen() = 0;

	static std::unique_ptr<Renderer> CreateBestRenderer();
};

#endif