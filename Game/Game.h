#pragma once
#include "core.h"
#include "Object/Scene.h"

class Game
{
public:
	enum class eState
	{
		START_AUDIO,
		TITLE,
		INIT_GAME,
		START_GAME,
		GAME,
		BOSS_FIGHT,
		PLAYER_DEAD,
		GAME_WAIT,
		GAME_OVER
	};

public:
	void Initialize();

	bool Update(float dt);
	void Draw(Core::Graphics& graphics);

	void AddPoints(int points) { m_score += points; }
	void AddLives(int lives) { m_lives += lives; }

	void SetState(eState state) { m_state = state; }

protected:
	eState m_state{ eState::START_AUDIO };

	int m_score{ 0 };
	int m_lives{ 3 };
	int m_highScore{ 0 };

	nc::Scene m_scene;

	float m_frameTime;
	float m_spawnTimer{ 0 };
	float m_stateTimer{ 0 };
	float m_oneUpTimer{ 0 };
	float m_scoreBoostTimer{ 0 };
	float m_bossTimer{ 0 };
};

