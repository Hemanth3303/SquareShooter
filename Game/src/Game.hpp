#pragma once

#include "pch.hpp"
#include "Entity.hpp"
#include "Player.hpp"

class Game {
public:
	Game(int32_t winWidth, int32_t winHeight, std::string&& winTitle, bool isResizable = false);
	~Game();

	void initEntities();
	void run();

private:

	void handleEvents();
	void update(float dt);
	void render();

	inline double getTimeInMilliSeconds() const { return (GetTime() * 1000.0); }
	inline double getTimeInNanoSeconds() const { return (GetTime() * 1000000000.0); }

private:
	int32_t m_WinWidth, m_WinHeight;
	int32_t m_TargetFPS = 60, m_TargetUPS = 60;
	int32_t m_FPS = 0, m_UPS = 0;
	std::string m_WinTitle;
	bool m_IsRunning = false;

	int32_t m_Score = 0;

	std::shared_ptr<Entity> m_Player;
	std::vector<std::shared_ptr<Entity>> m_Entities;
};