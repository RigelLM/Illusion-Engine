#include "Map.h"

Map::Map(glm::vec2 size)
	:m_Size(size)
{
	Illusion::Ref<GameObject> bed = std::make_shared<GameObject>("assets/textures/hotel_room/BED.png");
	Illusion::Ref<GameObject> chair = std::make_shared<GameObject>("assets/textures/hotel_room/CHAIR.png");
	Illusion::Ref<GameObject> desk = std::make_shared<GameObject>("assets/textures/hotel_room/DESK.png");
	Illusion::Ref<GameObject> pic = std::make_shared<GameObject>("assets/textures/hotel_room/PIC3.png");
	Illusion::Ref<GameObject> door = std::make_shared<GameObject>("assets/textures/hotel_room/DOOR_FRONT.png");
	Illusion::Ref<GameObject> door_side = std::make_shared<GameObject>("assets/textures/hotel_room/DOOR_SIDE.png");

	m_GameObjects.push_back(bed);
	m_GameObjects.push_back(chair);
	m_GameObjects.push_back(desk);
	m_GameObjects.push_back(pic);
	m_GameObjects.push_back(door);
	m_GameObjects.push_back(door_side);
}

void Map::LoadAssets(std::string path)
{
	m_MapTexture.reset(new Illusion::Texture2D(path));
	for (auto go : m_GameObjects)
	{
		go->LoadAssets();
	}
}

void Map::OnUpdate(Illusion::Timestep ts, glm::vec2 player_pos)
{
	for (auto go : m_GameObjects)
	{
		go->OnUpdate(player_pos);
	}
}

void Map::OnEvent(Illusion::Event& e, glm::vec2 player_pos)
{
	for (auto go : m_GameObjects)
	{
		go->OnEvent(e, player_pos);
	}
}

void Map::OnRender()
{
	Illusion::Renderer2D::DrawQuad({ 0.0f,0.0f,0.4f }, m_Size, m_MapTexture);
}