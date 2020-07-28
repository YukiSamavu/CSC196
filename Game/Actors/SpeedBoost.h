#pragma once
#include "Object/Actor.h"

class SpeedBoost : public nc::Actor
{
public:
	SpeedBoost() {}

	virtual eType GetType() override { return eType::SPEEDBOOST; }

	virtual bool Load(const std::string& filename) override;
	virtual void Update(float dt) override;

	virtual void OnCollision(Actor* actor) override;
};
