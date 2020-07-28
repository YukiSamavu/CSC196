#pragma once
#include "Object/Actor.h"

class OneUp : public nc::Actor
{
public:
	OneUp() {}

	virtual eType GetType() override { return eType::ONEUP; }

	virtual bool Load(const std::string& filename) override;
	virtual void Update(float dt) override;

	virtual void OnCollision(Actor* actor) override;
};