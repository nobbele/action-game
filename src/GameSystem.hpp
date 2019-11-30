#ifndef AG_GAMESYSTEM_H
#define AG_GAMESYSTEM_H

class Renderer;
class EventHandler;

class GameSystem {
public:
	GameSystem();

	inline Renderer& GetRenderer() {
		return *renderer;
	}

	inline EventHandler& GetEventHandler() {
		return *eventHandler;
	}

	static GameSystem& GetInstance();

	protected:
	std::unique_ptr<Renderer> renderer;
	std::unique_ptr<EventHandler> eventHandler;
};

#endif