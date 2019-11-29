#ifndef GAMESYSTEM_H
#define GAMESYSTEM_H

#include "Graphics/Renderer.hpp"
#include "EventHandler.hpp"

class GameSystem {
public:
	std::unique_ptr<Renderer> renderer;
	std::unique_ptr<EventHandler> eventHandler;
	GameSystem();

	GameSystem(GameSystem const&) = delete;
    void operator=(GameSystem const&)  = delete;

	static GameSystem& GetInstance();
};

#endif