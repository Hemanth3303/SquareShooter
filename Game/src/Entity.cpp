#include "pch.hpp"
#include "Entity.hpp"

Entity::Entity(float x, float y, float w, float h) 
	: m_Bounds(Rectangle(x, y, w, h)) {

}

Entity::~Entity() {

}

void Entity::handleEvents() {

}

void Entity::update(float dt) {
	m_Bounds.x += (m_Vel.x * m_Speed * dt);
	m_Bounds.y += (m_Vel.y * m_Speed * dt);

	customUpdates(dt);
}

void Entity::render() {
	DrawRectangleRec(m_Bounds, RED);
}
