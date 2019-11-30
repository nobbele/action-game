#ifndef AG_SFMLEVENTHANDLER_H
#define AG_SFMLEVENTHANDLER_H

#include "EventHandler.hpp"

class SFMLEventHandler : public EventHandler {
public:
	sf::Window& window;
	SFMLEventHandler(Renderer& renderer);
	void PollEvents();
	void Raise(EventHandler::Event e, EventHandler::EventParameter&& param);
};

#endif