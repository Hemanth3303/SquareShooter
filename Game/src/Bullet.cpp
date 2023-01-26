#include "pch.hpp"
#include "Bullet.hpp"

Bullet::Bullet(float x, float y, float w, float h) 
	:Entity(x, y, w, h) {
	m_Speed = 30;

	float distX = (GetMouseX() - m_Bounds.x);
	float distY = (GetMouseY() - m_Bounds.y);

	float angle = atan2f(distY, distX);

	m_Vel.x = cosf(angle) * m_Speed;
	m_Vel.y = sinf(angle) * m_Speed;
}

void Bullet::render() {
	DrawRectangleRec(m_Bounds, MAGENTA);
}

void Bullet::customUpdates(float dt) {
	if (m_Bounds.x < 0 || m_Bounds.x > GetScreenWidth() ||
		m_Bounds.y < 0 || m_Bounds.y > GetScreenHeight()) {
		m_CanDelete = true;
	}
}
