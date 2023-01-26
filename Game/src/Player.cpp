#include "pch.hpp"
#include "Player.hpp"

Player::Player(float x, float y, float w, float h)
	: Entity(x, y, w, h) {

}

Player::~Player() {

}

void Player::handleEvents() {
	if (IsKeyDown(KEY_A) && IsKeyDown(KEY_D)) {
		m_Vel.x = 0;
	}
	else {
		if (IsKeyDown(KEY_A)) {
			m_Vel.x = -1;
		}
		if (IsKeyDown(KEY_D)) {
			m_Vel.x = 1;
		}
	}
	
	if (IsKeyDown(KEY_S) && IsKeyDown(KEY_W)) {
		m_Vel.y = 0;
	}
	else {
		if (IsKeyDown(KEY_W)) {
			m_Vel.y = -1;
		}
		if (IsKeyDown(KEY_S)) {
			m_Vel.y = 1;
		}
	}

	if (IsKeyReleased(KEY_A)) {
		m_Vel.x = 0;
	}
	if (IsKeyReleased(KEY_D)) {
		m_Vel.x = 0;
	}
	if (IsKeyReleased(KEY_W)) {
		m_Vel.y = 0;
	}
	if (IsKeyReleased(KEY_S)) {
		m_Vel.y = 0;
	}

}

void Player::render() {
	DrawRectangleRec(m_Bounds, Color(31, 81, 255, 255));
	for (auto& bullet : m_Bullets) {
		bullet.render();
	}
}

void Player::customUpdates(float dt) {
	if (m_Bounds.x < 0) {
		m_Bounds.x = 0;
	}
	if (m_Bounds.x + m_Bounds.width > GetScreenWidth()) {
		m_Bounds.x = GetScreenWidth() - m_Bounds.width;
	}
	if (m_Bounds.y < 0) {
		m_Bounds.y = 0;
	}
	if (m_Bounds.y + m_Bounds.height > GetScreenHeight()) {
		m_Bounds.y = GetScreenHeight() - m_Bounds.height;
	}

	for (size_t i = 0; i < m_Bullets.size(); i++) {
		m_Bullets[i].update(dt);
		if (m_Bullets[i].canDelete()) {
			m_Bullets.erase(m_Bullets.begin() + i);
			break;
		}
	}

	shootTimer += dt;

}

void Player::shootBullets() {
	if (shootTimer > 0.5f) {
		m_Bullets.emplace_back(m_Bounds.x + m_Bounds.width / 4, m_Bounds.y + m_Bounds.height / 4, 10.0f, 10.0f);
		shootTimer = 0.0f;
	}
}
