#include "EventHandler.hpp"
#include "_SFMLEventHandler.hpp"

std::ostream& operator<<(std::ostream& os, const EventHandler::EKey key) {
	return os << static_cast<uint>(key);
}

std::unique_ptr<EventHandler> EventHandler::CreateBestEventHandler(Renderer& renderer) {
	return std::make_unique<SFMLEventHandler>(renderer);
}