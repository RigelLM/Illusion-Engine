#pragma once

#include <Engine.h>

#include "GameObject.h"

class Map
{
public:

	Map(glm::vec2 size);

	void LoadAssets(std::string path);

	void OnUpdate(Illusion::Timestep ts, glm::vec2 player_pos);
	void OnEvent(Illusion::Event& e, glm::vec2 player_pos);
	void OnRender();


private:

	std::string m_Name;

	glm::vec2 m_Size;

	Illusion::Ref<Illusion::Texture2D> m_MapTexture;

	std::vector<Illusion::Ref<GameObject>> m_GameObjects;

};

