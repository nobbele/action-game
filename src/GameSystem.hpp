#ifndef AG_GAMESYSTEM_H
#define AG_GAMESYSTEM_H

class Renderer;
class EventHandler;

class GameSystem {
public:
	std::unique_ptr<Renderer> renderer;
	std::unique_ptr<EventHandler> eventHandler;
	GameSystem();

	static GameSystem& GetInstance();
};

#endif