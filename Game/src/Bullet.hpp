#pragma once

#include "pch.hpp"
#include "Entity.hpp"

class Bullet : public Entity {
public:
	Bullet(float x, float y, float w, float h);
	virtual void render() override;
	virtual void customUpdates(float dt) override;
	
	inline const bool& canDelete() const { return m_CanDelete; }
private:
	bool m_CanDelete = false;
};