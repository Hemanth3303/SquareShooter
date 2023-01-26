#pragma once

#include "pch.hpp"
#include "Entity.hpp"
#include "Bullet.hpp"

class Player : public Entity {
public:
	Player(float x, float y, float w, float h);
	~Player();

	virtual void handleEvents() override;
	virtual void render() override;
	virtual void customUpdates(float dt) override;
private:
	std::vector<Bullet> m_Bullets;
private:
	void shootBullets();
	float shootTimer = 2.0f;
};