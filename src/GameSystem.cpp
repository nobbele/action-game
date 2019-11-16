#include "GameSystem.hpp"

GameSystem::GameSystem()
	: renderer(Renderer::CreateBestRenderer()), eventHandler(EventHandler::CreateBestEventHandler(*renderer)) {
}

GameSystem& GameSystem::GetInstance() {
	static GameSystem instance;
	return instance;
}