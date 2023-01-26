#pragma once

#include "pch.hpp"
#include "Entity.hpp"

class Player : public Entity {
public:
	Player(float x, float y, float w, float h);
	~Player();

	virtual void handleEvents() override;
	virtual void render() override;
	virtual void customUpdates(float dt) override;
};