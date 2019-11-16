#include "EventHandler.hpp"
#include "_SFMLEventHandler.hpp"

std::unique_ptr<EventHandler> EventHandler::CreateBestEventHandler(Renderer& renderer) {
	return std::make_unique<SFMLEventHandler>(renderer);
}