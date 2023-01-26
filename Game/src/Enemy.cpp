#include "pch.hpp"
#include "Enemy.hpp"

Enemy::Enemy(float x, float y, float w, float h, const std::unique_ptr<Player>& player)
	: Entity(x, y ,w, h), m_Player(player) {

}

void Enemy::customUpdates(float dt) {

	m_Speed = 20;

	float distX = (m_Player->getBounds().x - m_Bounds.x);
	float distY = (m_Player->getBounds().y - m_Bounds.y);

	float angle = atan2f(distY, distX);

	m_Vel.x = cosf(angle) * m_Speed;
	m_Vel.y = sinf(angle) * m_Speed;
}
