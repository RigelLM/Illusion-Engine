#include "GameLayer.h"

#include "Engine/Core/Utils/Random.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

GameLayer::GameLayer()
	:Layer("GameLayer")
{
	auto& window = Illusion::Application::Get().GetWindow();
	CreateCamera(window.GetWidth(), window.GetHeight());

	Illusion::Random::Init();
}

void GameLayer::OnAttach()
{
	m_Level.Init();
}

void GameLayer::OnDetach()
{

}

void GameLayer::OnUpdate(Illusion::Timestep ts)
{

	if (m_Level.IsGameOver())
		m_State = GameState::GameOver;

	const auto& playerPos = m_Level.GetPlayer().GetPosition();
	m_Camera->SetPosition({ playerPos.x, playerPos.y, 0.0f });

	switch (m_State)
	{
		case GameState::Play:
		{
			m_Level.OnUpdate(ts);

			break;
		}
	}
	// Render
	Illusion::RenderCommand::Clear({ 0.0f, 0.0f, 0.0f, 1.0 });
	Illusion::Renderer2D::BeginScene(*m_Camera);

	m_Level.OnRender();

	Illusion::Renderer2D::EndScene();
}

void GameLayer::OnEvent(Illusion::Event& event)
{
	m_Level.OnEvent(event);

	Illusion::EventDispatcher dispatcher(event);
	dispatcher.Dispatch<Illusion::WindowResizeEvent>(ENGINE_BIND_EVENT_FN(GameLayer::OnWindowResize));
	dispatcher.Dispatch<Illusion::MouseButtonPressedEvent>(ENGINE_BIND_EVENT_FN(GameLayer::OnMouseButtonPressed));
}

bool GameLayer::OnMouseButtonPressed(Illusion::MouseButtonPressedEvent& e)
{
	if (m_State == GameState::GameOver)
		m_Level.Reset();

	m_State = GameState::Play;
	return false;
}

bool GameLayer::OnWindowResize(Illusion::WindowResizeEvent& e)
{
	CreateCamera(e.GetWidth(), e.GetHeight());
	return false;
}

void GameLayer::CreateCamera(uint32_t width, uint32_t height)
{
	float aspectRatio = (float)width / (float)height;

	float camWidth = 8.0f;
	float bottom = -camWidth;
	float top = camWidth;
	float left = bottom * aspectRatio;
	float right = top * aspectRatio;
	m_Camera = Illusion::CreateScope<Illusion::Camera>(left, right, bottom, top);
}