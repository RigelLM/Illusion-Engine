#include "Player.h"

#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>

Player::Player()
{
}

void Player::LoadAssets()
{
	left.reset(new Illusion::SequenceAnimation(16, "assets/animations/chicken/move/left", "left"));
	right.reset(new Illusion::SequenceAnimation(16, "assets/animations/chicken/move/right", "right"));
	up.reset(new Illusion::SequenceAnimation(16, "assets/animations/chicken/move/up", "up"));
	down.reset(new Illusion::SequenceAnimation(16, "assets/animations/chicken/move/down", "down"));

	left_up.reset(new Illusion::SequenceAnimation(16, "assets/animations/chicken/move/left_up", "left_up"));
	left_down.reset(new Illusion::SequenceAnimation(16, "assets/animations/chicken/move/left_down", "left_down"));
	right_up.reset(new Illusion::SequenceAnimation(16, "assets/animations/chicken/move/right_up", "right_up"));
	right_down.reset(new Illusion::SequenceAnimation(16, "assets/animations/chicken/move/right_down", "right_down"));

	stay_left.reset(new Illusion::SequenceAnimation(1, "assets/animations/chicken/stay/left", "left"));
	stay_right.reset(new Illusion::SequenceAnimation(1, "assets/animations/chicken/stay/right", "right"));
	stay_up.reset(new Illusion::SequenceAnimation(1, "assets/animations/chicken/stay/up", "up"));
	stay_down.reset(new Illusion::SequenceAnimation(1, "assets/animations/chicken/stay/down", "down"));

	stay_left_up.reset(new Illusion::SequenceAnimation(1, "assets/animations/chicken/stay/left_up", "left_up"));
	stay_left_down.reset(new Illusion::SequenceAnimation(1, "assets/animations/chicken/stay/left_down", "left_down"));
	stay_right_up.reset(new Illusion::SequenceAnimation(1, "assets/animations/chicken/stay/right_up", "right_up"));
	stay_right_down.reset(new Illusion::SequenceAnimation(1, "assets/animations/chicken/stay/right_down", "right_down"));

	m_MoveAnims[Left] = left;
	m_MoveAnims[Right] = right;
	m_MoveAnims[Up] = up;
	m_MoveAnims[Down] = down;

	m_MoveAnims[Left_Up] = left_up;
	m_MoveAnims[Left_Down] = left_down;
	m_MoveAnims[Right_Up] = right_up;
	m_MoveAnims[Right_Down] = right_down;

	m_StayAnims[Left] = stay_left;
	m_StayAnims[Right] = stay_right;
	m_StayAnims[Up] = stay_up;
	m_StayAnims[Down] = stay_down;

	m_StayAnims[Left_Up] = stay_left_up;
	m_StayAnims[Left_Down] = stay_left_down;
	m_StayAnims[Right_Up] = stay_right_up;
	m_StayAnims[Right_Down] = stay_right_down;
}

void Player::OnUpdate(Illusion::Timestep ts)
{
	bool up = Illusion::Input::IsKeyPressed(ILLUSION_KEY_W) || Illusion::Input::IsKeyPressed(ILLUSION_KEY_UP);
	bool down = Illusion::Input::IsKeyPressed(ILLUSION_KEY_S) || Illusion::Input::IsKeyPressed(ILLUSION_KEY_DOWN);
	bool left = Illusion::Input::IsKeyPressed(ILLUSION_KEY_A) || Illusion::Input::IsKeyPressed(ILLUSION_KEY_LEFT);
	bool right = Illusion::Input::IsKeyPressed(ILLUSION_KEY_D) || Illusion::Input::IsKeyPressed(ILLUSION_KEY_RIGHT);

	bool move = up || down || left || right;

	AT h = NONE;
	AT v = NONE;

	if (move)
	{
		m_Moving = true;

		if (down)
		{
			v = DOWN;
			m_Velocity = glm::vec2(0.0f, -5.0f);
			m_Position += m_Velocity * (float)ts;
		}
		else if (up)
		{
			v = UP;
			m_Velocity = glm::vec2(0.0f, 5.0f);
			m_Position += m_Velocity * (float)ts;
		}
		if (left)
		{
			h = LEFT;
			m_Velocity = glm::vec2(-5.0f, 0.0f);
			m_Position += m_Velocity * (float)ts;
		}
		else if (right)
		{
			h = RIGHT;
			m_Velocity = glm::vec2(5.0f, 0.0f);
			m_Position += m_Velocity * (float)ts;
		}

		if (!((h | v) ^ (LEFT)))
			m_AnimType = Left;
		else if (!((h | v) ^ (RIGHT)))
			m_AnimType = Right;
		else if (!((h | v) ^ (DOWN)))
			m_AnimType = Down;
		else if (!((h | v) ^ (UP)))
			m_AnimType = Up;
		else if (!((h | v) ^ (LEFT | UP)))
			m_AnimType = Left_Up;
		else if (!((h | v) ^ (LEFT | DOWN)))
			m_AnimType = Left_Down;
		else if (!((h | v) ^ (RIGHT | UP)))
			m_AnimType = Right_Up;
		else if (!((h | v) ^ (RIGHT | DOWN)))
			m_AnimType = Right_Down;
	}
	else
	{
		m_Moving = false;
	}
}
void Player::OnRender()
{
	if (m_Moving)
		m_MoveAnims[m_AnimType]->Play({ m_Position.x, m_Position.y, 0.5f });
	else
		m_StayAnims[m_AnimType]->Play({ m_Position.x, m_Position.y, 0.5f });
	//Illusion::Renderer2D::DrawQuad({ m_Position.x, m_Position.y, 0.5f }, { 1.0f, 1.3f },  m_ShipTexture);
}

void Player::Reset()
{
	m_Position = { -10.0f, 0.0f };
	m_Velocity = { 5.0f, 0.0f };
}

