#include "pch.hpp"
#include "Game.hpp"

Game::Game(int32_t winWidth, int32_t winHeight, std::string&& winTitle, bool isResizable) 
	: m_WinWidth(winWidth), m_WinHeight(winHeight), m_WinTitle(std::move(winTitle)) {

	if (isResizable) {
		SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	}

	InitWindow(m_WinWidth, m_WinHeight, m_WinTitle.c_str());

	m_IsRunning = true;

	initEntities();
}

Game::~Game() {
	CloseWindow();
}

void Game::initEntities() {
	std::unique_ptr<Entity> player = std::make_unique<Player>(100.0f, 100.0f, 50.0f, 50.0f);
	m_Entities.emplace_back(std::move(player));
}

void Game::run() {

	double timerPerFrame = 1000000000.0 / m_TargetFPS;
	double timerPerUpdate = 1000000000.0 / m_TargetUPS;

	double prevTime = getTimeInNanoSeconds();
	int32_t updates = 0, frames = 0;

	double lastCheck = getTimeInMilliSeconds();
	double deltaUPS = 0, deltaFPS = 0;

	double dt = 1.0 / m_TargetUPS;

	while (m_IsRunning) {
		double currentTime = getTimeInNanoSeconds();
		deltaUPS += (currentTime - prevTime) / timerPerUpdate;
		deltaFPS += (currentTime - prevTime) / timerPerFrame;
		prevTime = currentTime;

		if (deltaUPS >= 1) {
			handleEvents();
			update(static_cast<float>(dt));
			updates++;
			deltaUPS--;
		}

		if (deltaFPS >= 1) {
			render();
			frames++;
			deltaFPS--;
		}

		if (getTimeInMilliSeconds() - lastCheck >= 1000) {
			lastCheck = getTimeInMilliSeconds();
			m_FPS = frames;
			m_UPS = updates;
			dt = (1.0 / m_UPS);
			frames = 0;
			updates = 0;
			//std::cout << "FPS: " << m_FPS << " | UPS: " << m_UPS << "\n";
		}
	}
}

void Game::handleEvents() {
	for (const auto& entity : m_Entities) {
		entity->handleEvents();
	}
}

void Game::update(float dt) {
	if (WindowShouldClose()) {
		m_IsRunning = false;
	}
	for (const auto& entity : m_Entities) {
		entity->update(dt);
	}
}

void Game::render() {
	BeginDrawing();
	ClearBackground(Color(0, 154, 23, 255));

	for (const auto& entity : m_Entities) {
		entity->render();
	}

	EndDrawing();
}
