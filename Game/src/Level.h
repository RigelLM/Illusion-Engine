#pragma once

#include "Player.h"
#include "GameObject.h"
#include "Map.h"

class Level
{
public:
	void Init();

	void OnUpdate(Illusion::Timestep ts);
	void OnEvent(Illusion::Event& e);
	void OnRender();

	bool IsGameOver() const { return m_GameOver; }
	void Reset();

	Player& GetPlayer() { return m_Player; }

private:
	Collision CollisionTest();

	void GameOver();
private:
	Player m_Player;

	std::unordered_map<std::string, Illusion::Ref<Map>> m_Maps;

	bool m_GameOver = false;

	Illusion::Ref<Illusion::Texture2D> m_TriangleTexture;
};