#include "GameSystem.hpp"
#include "Graphics/Renderer.hpp"
#include "EventHandler.hpp"

GameSystem::GameSystem()
	: renderer(Renderer::CreateBestRenderer()), eventHandler(EventHandler::CreateBestEventHandler(*renderer)) {
}

GameSystem& GameSystem::GetInstance() {
	static GameSystem instance;
	return instance;
}