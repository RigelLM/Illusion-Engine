#include "GameObject.h"


GameObject::GameObject(std::string textpath)
{
	m_Texture.reset(new Illusion::Texture2D(textpath));
}

void GameObject::LoadAssets()
{
	m_Notice.reset(new Illusion::Texture2D("assets/textures/Notice.png"));
}

void GameObject::OnUpdate(glm::vec2 player_pos)
{
	glm::vec2 distance = m_Position - player_pos;
	if ((distance.x * distance.x + distance.y * distance.y) < m_DetectRadius * m_DetectRadius)
		m_Interactable = true;
	else
		m_Interactable = false;
}

void GameObject::OnRender()
{
	Illusion::Renderer2D::DrawQuad({ m_Position.x, m_Position.y, 0.6f }, { 0.76f * 1.5f,1.0f * 1.5f }, m_Texture);

	if(m_Interactable)
		Illusion::Renderer2D::DrawQuad({ m_Position.x + 0.8f, m_Position.y + 1.2f, 0.7f }, {1.0f * 1.5f, 0.76f * 1.5f }, m_Notice);

	//if (m_Active)
	//	Illusion::Renderer2D::DrawQuad({ 0.0f,0.0f, 1.0f }, { 10.425f, 12.5f }, m_Drawing);
}

void GameObject::OnEvent(Illusion::Event& e, glm::vec2 player_pos)
{
	glm::vec2 distance = m_Position - player_pos;
	if ((distance.x * distance.x + distance.y * distance.y) < m_DetectRadius * m_DetectRadius)
	{
		Illusion::EventDispatcher dispatcher(e);
		dispatcher.Dispatch<Illusion::KeyPressedEvent>(ENGINE_BIND_EVENT_FN(GameObject::OnKeyPressed));
	}
}

Collision GameObject::CollisionTest(glm::vec2 player_pos)
{
	glm::vec2 center = player_pos;
	// 计算AABB的信息（中心、半边长）
	glm::vec2 aabb_half_extents(0.75f, 1.0f);
	glm::vec2 aabb_center(
		m_Position.x - 0.25f,
		m_Position.y
	);
	// 获取两个中心的差矢量
	glm::vec2 difference = center - aabb_center;
	glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
	// AABB_center加上clamped这样就得到了碰撞箱上距离圆最近的点closest
	glm::vec2 closest = aabb_center + clamped;
	// 获得圆心center和最近点closest的矢量并判断是否 length <= radius
	difference = closest - center;

	if (glm::length(difference) < 1.0f)
		return std::make_tuple(true, CollideDir(difference), difference);
	else
		return std::make_tuple(false, UP, glm::vec2(0.0f, 0.0f));
}


bool GameObject::OnKeyPressed(Illusion::KeyPressedEvent& e)
{
	if (e.GetKeyCode() == ILLUSION_KEY_E)
	{
		m_Active = !m_Active;
		return false;
	}
}
