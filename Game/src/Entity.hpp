#pragma once

#include "pch.hpp"

class Entity {
public:
	Entity(float x, float y, float w, float h);
	virtual ~Entity();

	virtual void handleEvents();
	virtual void update(float dt);
	virtual void render();

	virtual void customUpdates(float dt) = 0;

	inline const Rectangle& getBounds() const { return m_Bounds; }

protected:
	Rectangle m_Bounds;
	Vector2 m_Vel = { 0, 0 };
	int32_t m_Speed = 500;
};