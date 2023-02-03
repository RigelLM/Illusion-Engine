#pragma once

#include <Engine.h>

class Player
{
public:
	Player();

	void LoadAssets();

	void OnUpdate(Illusion::Timestep ts);
	void OnRender();

	void Reset();

	const glm::vec2& GetPosition() const { return m_Position; }

	void SetPosition(glm::vec2 pos) { m_Position = pos; }

private:
	glm::vec2 m_Position = { -10.0f, 0.0f };
	glm::vec2 m_Velocity = { 5.0f, 0.0f };

	enum AT
	{
		NONE		= 0,
		LEFT		= BIT(1),
		RIGHT		= BIT(2),
		UP			= BIT(3),
		DOWN		= BIT(4),
	};

	enum Animation
	{
		Left, Right, Up, Down, Left_Up, Left_Down, Right_Up, Right_Down
	};

	Animation m_AnimType = Right;
	bool m_Moving = false;

	Illusion::Ref<Illusion::SequenceAnimation> left, right, up, down;
	Illusion::Ref<Illusion::SequenceAnimation> left_up, left_down, right_up, right_down;

	Illusion::Ref<Illusion::SequenceAnimation> stay_left, stay_right, stay_up, stay_down;
	Illusion::Ref<Illusion::SequenceAnimation> stay_left_up, stay_left_down, stay_right_up, stay_right_down;

	std::unordered_map<Animation, Illusion::Ref<Illusion::SequenceAnimation>> m_MoveAnims, m_StayAnims;
};