#ifndef _SFMLEVENTHANDLER_H
#define _SFMLEVENTHANDLER_H

#include "EventHandler.hpp"

class SFMLEventHandler : public EventHandler {
public:
	sf::Window& window;
	SFMLEventHandler(Renderer& renderer);
	void PollEvents();
	void Raise(EventHandler::Event e);
};

#endif