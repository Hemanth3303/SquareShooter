#pragma once

#include "pch.hpp"
#include "Entity.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "States.hpp"
#include "AudioManager.hpp"

class Game {
public:
	Game(int32_t winWidth, int32_t winHeight, std::string&& winTitle, bool isResizable = false);
	~Game();

	void run();

private:
	void init();

	void handleEvents();
	void update(float dt);
	void playingUpdate(float dt);

	void render();
	void menuRender();
	void playingRender();
	void gameOverRender();

	void handlePlayerEnemyCollision();
	void handleBulletEnemyCollision();

	inline double getTimeInMilliSeconds() const { return (GetTime() * 1000.0); }
	inline double getTimeInNanoSeconds() const { return (GetTime() * 1000000000.0); }

private:
	int32_t m_WinWidth, m_WinHeight;
	int32_t m_TargetFPS = 60, m_TargetUPS = 60;
	int32_t m_FPS = 0, m_UPS = 0;
	std::string m_WinTitle;
	bool m_IsRunning = false;
	States m_State = States::Menu;

	int32_t m_Score = 0;
	double m_EnemyTimer = 0.0;

	std::unique_ptr<Player> m_Player;
	std::vector<std::shared_ptr<Enemy>> m_Enemies;
};