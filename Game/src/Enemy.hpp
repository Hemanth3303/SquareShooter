#pragma once

#include "pch.hpp"
#include "Entity.hpp"
#include "Player.hpp"

class Enemy : public Entity {
public:
	Enemy(float x, float y, float w, float h, const std::unique_ptr<Player>& player);
	virtual void customUpdates(float dt) override;

	inline const bool isEnemy() const { return true; }
private:
	const std::unique_ptr<Player>& m_Player;
};