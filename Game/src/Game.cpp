#include "pch.hpp"
#include "Game.hpp"

Game::Game(int32_t winWidth, int32_t winHeight, std::string&& winTitle, bool isResizable) 
	: m_WinWidth(winWidth), m_WinHeight(winHeight), m_WinTitle(std::move(winTitle)) {

	if (isResizable) {
		SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	}

	InitWindow(m_WinWidth, m_WinHeight, m_WinTitle.c_str());

	m_IsRunning = true;

	AudioManager::Init();

	init();
}

Game::~Game() {
	AudioManager::ShutDown();
	CloseWindow();
}

void Game::run() {

	double timerPerFrame = 1000000000.0 / m_TargetFPS;
	double timerPerUpdate = 1000000000.0 / m_TargetUPS;

	double prevTime = getTimeInNanoSeconds();
	int32_t updates = 0, frames = 0;

	double lastCheck = getTimeInMilliSeconds();
	double deltaUPS = 0, deltaFPS = 0;

	double dt = 1.0 / m_TargetUPS;

	AudioManager::PlayBgMusic();

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
			//std::cout << "GAME STATE: " << m_State << "\n";
		}
	}
}

void Game::handleEvents() {
	m_Player->handleEvents();
	for (const auto& enemy : m_Enemies) {
		enemy->handleEvents();
	}

	switch (m_State) {
		case States::Menu:
			if (IsKeyPressed(KEY_SPACE)) {
				m_State = States::Playing;
			}
			break;
		case States::Playing:
			if (IsKeyPressed(KEY_P)) {
				m_State = States::Pause;
			}
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				m_Player->shootBullets();
			}
			break;
		case States::Pause:
			if (IsKeyPressed(KEY_P)) {
				m_State = States::Playing;
			}
			break;
		case States::GameOver:
			if (IsKeyPressed(KEY_R)) {
				init();
				m_State = States::Playing;
			}
			break;
	}
}

void Game::init() {
	m_Player.reset();
	m_Enemies.clear();
	m_Player = std::make_unique<Player>(300.0f, 200.0f, 50.0f, 50.0f);
	m_Score = 0;
	m_State = States::Menu;
}

void Game::update(float dt) {
	if (WindowShouldClose()) {
		m_IsRunning = false;
	}
	AudioManager::UpdateBgMusic();
	switch (m_State) {
		case States::Playing:
			playingUpdate(dt);
			break;
	}
}

void Game::playingUpdate(float dt) {
	m_Player->update(dt);
	for (const auto& enemy : m_Enemies) {
		enemy->update(dt);
	}

	m_EnemyTimer += dt;
	if (m_EnemyTimer > 1.5) {
		m_EnemyTimer = 0.0;

		int32_t enemyX = 0, enemyY = 0;
		int radius = GetRandomValue(10, 25);

		if (GetRandomValue(0, 1) < 0.5) {
			enemyX = GetRandomValue(0, 1) < 0.5 ? 0 - radius : m_WinWidth + radius;
			enemyY = GetRandomValue(0, m_WinHeight);
		}
		else {
			enemyX = GetRandomValue(0, m_WinWidth);
			enemyY = GetRandomValue(0, 1) < 0.5 ? 0 - radius : m_WinHeight + radius;
		}

		m_Enemies.emplace_back(std::make_shared<Enemy>(static_cast<float>(enemyX), static_cast<float>(enemyY), 30.0f, 30.0f, m_Player));
	}

	handlePlayerEnemyCollision();
	handleBulletEnemyCollision();
}

void Game::render() {
	BeginDrawing();
	ClearBackground(Color(0, 154, 23, 255));
	
	switch (m_State) {
		case States::Menu:
			menuRender();
			break;
		case States::Playing:
			playingRender();
			break;
		case States::Pause:
			playingRender();
			DrawText("Press P to UnPause", m_WinWidth / 2 - 180, 300, 32, BLACK);
			break;
		case States::GameOver:
			gameOverRender();
			break;
	}

	EndDrawing();
}

void Game::menuRender() {
	DrawText("Square Shooter", m_WinWidth / 2 - 180 , 200, 32, BLACK);
	DrawText("Press Space Key To Start", m_WinWidth / 2 - 180, 300, 32, BLACK);
	DrawText("Press P Key To Pause", m_WinWidth / 2 - 180, 350, 32, BLACK);
	DrawText("Press WASD To Move", m_WinWidth / 2 - 180, 400, 32, BLACK);
}

void Game::playingRender() {
	DrawText("SCORE: ", 0, 0, 32, BLACK);
	DrawText(std::to_string(m_Score).c_str(), 130, 0, 32, BLACK);

	m_Player->render();
	for (const auto& enemy : m_Enemies) {
		enemy->render();
	}
}

void Game::gameOverRender() {
	DrawText("Your Score Was: ", m_WinWidth / 2 - 180, 240, 32, BLACK);
	DrawText(std::to_string(m_Score).c_str(), m_WinWidth / 2 + 100, 240, 32, BLACK);
	DrawText("Press R to restart", m_WinWidth / 2 - 180, 300, 32, BLACK);
}

void Game::handlePlayerEnemyCollision() {
	for (auto& enemy : m_Enemies) {
		if (CheckCollisionRecs(m_Player->getBounds(), enemy->getBounds())) {
			m_State = States::GameOver;
			AudioManager::PlayDieSound();
		}
	}
}

void Game::handleBulletEnemyCollision() {
	for (size_t i = 0; i < m_Player->getBullets().size(); i++) {
		for (size_t j = 0; j < m_Enemies.size(); j++) {
			if (CheckCollisionRecs(m_Player->getBullets()[i].getBounds(), m_Enemies[j]->getBounds())) {
				m_Score++;
				m_Player->getBullets().erase(m_Player->getBullets().begin() + i);
				m_Enemies.erase(m_Enemies.begin() + j);
				AudioManager::PlayHitSound();
				return;
			}
		}
	}
}
