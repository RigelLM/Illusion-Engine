#pragma once

#include <Engine.h>

enum Direction {
	UP,
	RIGHT,
	DOWN,
	LEFT
};

typedef std::tuple<bool, Direction, glm::vec2> Collision;

class GameObject
{
public:

	GameObject(std::string textpath);

	void LoadAssets();

	void OnUpdate(glm::vec2 player_pos);
	void OnRender();

	void OnEvent(Illusion::Event& e, glm::vec2 player_pos);

	Collision CollisionTest(glm::vec2 player_pos);

	const glm::vec2& GetPosition() const { return m_Position; }

	bool OnKeyPressed(Illusion::KeyPressedEvent& e);

private:
	inline Direction CollideDir(glm::vec2 target)
	{
		glm::vec2 compass[] = {
			glm::vec2(0.0f, 1.0f),  // ио
			glm::vec2(1.0f, 0.0f),  // ср
			glm::vec2(0.0f, -1.0f), // об
			glm::vec2(-1.0f, 0.0f)  // вС
		};
		float max = 0.0f;
		int best_match = -1;
		for (int i = 0; i < 4; i++)
		{
			float dot_product = glm::dot(glm::normalize(target), compass[i]);
			if (dot_product > max)
			{
				max = dot_product;
				best_match = i;
			}
		}
		return (Direction)best_match;
	}

private:

	Illusion::Ref<Illusion::Texture2D> m_Notice;

	Illusion::Ref<Illusion::Texture2D> m_Texture;
	Illusion::Ref<Illusion::Texture2D> m_Drawing;

	glm::vec2 m_Position = { 0.0f, 0.0f };

	float m_DetectRadius = 3.5f;

	bool m_Interactable = false;
	bool m_Active = false;
};

