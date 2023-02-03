#include "Level.h"

#include "Engine/Core/Utils/Random.h"

#include <glm/gtc/matrix_transform.hpp>


void Level::Init()
{
	Illusion::Ref<Map> hotel_room = std::make_shared<Map>(glm::vec2(25.0f, 14.40f));
	hotel_room->LoadAssets("assets/textures/hotel_room/room.png");
	m_Maps["hotel_room"] = hotel_room;

	m_Player.LoadAssets();
}

void Level::OnUpdate(Illusion::Timestep ts)
{
	m_Player.OnUpdate(ts);

	m_Maps["hotel_room"]->OnUpdate(ts, m_Player.GetPosition());

	Collision collision = CollisionTest();
	if (std::get<0>(collision)) // 如果collision 是 true
	{
		// 碰撞处理
		Direction dir = std::get<1>(collision);
		glm::vec2 diff_vector = std::get<2>(collision);
		if (dir == LEFT || dir == RIGHT) // 水平方向碰撞
		{
			// 重定位
			float penetration = 1.0f - std::abs(diff_vector.x);
			if (dir == LEFT)
				m_Player.SetPosition(glm::vec2(m_Player.GetPosition().x + penetration, m_Player.GetPosition().y)); // 将球右移
			else
				m_Player.SetPosition(glm::vec2(m_Player.GetPosition().x - penetration, m_Player.GetPosition().y)); // 将球左移
		}
		else // 垂直方向碰撞
		{
			// 重定位
			float penetration = 1.0f - std::abs(diff_vector.y);
			if (dir == UP)
				m_Player.SetPosition(glm::vec2(m_Player.GetPosition().x, m_Player.GetPosition().y - penetration)); // 将球上移
			else
				m_Player.SetPosition(glm::vec2(m_Player.GetPosition().x, m_Player.GetPosition().y + penetration)); // 将球下移
		}

	}
}

void Level::OnEvent(Illusion::Event& e)
{
	m_Maps["hotel_room"]->OnEvent(e, m_Player.GetPosition());
}

void Level::OnRender()
{
	const auto& playerPos = m_Player.GetPosition();

	// Background
	Illusion::Renderer2D::DrawQuad({ playerPos.x, 0.0f, -0.8f }, { 50.0f, 50.0f }, { 0.3f, 0.3f, 0.3f, 1.0f });

	// Floor and ceiling
	//Illusion::Renderer2D::DrawQuad({ playerPos.x,  34.0f }, { 50.0f, 50.0f }, { 0.0f, 0.8f, 0.8f, 1.0f });
	//Illusion::Renderer2D::DrawQuad({ playerPos.x, -34.0f }, { 50.0f, 50.0f }, { 0.0f, 0.8f, 0.8f, 1.0f });

	m_Maps["hotel_room"]->OnRender();
	m_Player.OnRender();
}

Collision Level::CollisionTest()
{
	//return m_TestObject.CollisionTest(m_Player.GetPosition());
	return std::make_tuple(false, UP, glm::vec2(0.0f, 0.0f));
}

void Level::GameOver()
{
	m_GameOver = true;
}

void Level::Reset()
{
	m_GameOver = false;

	m_Player.Reset();
}