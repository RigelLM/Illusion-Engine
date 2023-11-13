#include "GameLayer.h"

#include "Tracker.h"

GameLayer::GameLayer()
	:Layer("GameLayer")
{

}

void GameLayer::OnAttach()
{
	m_ActiveScene = Illusion::CreateRef<Illusion::Scene>();

	m_SqureEntity = m_ActiveScene->CreateEntity("Square");
	m_SqureEntity.AddComponent<Illusion::SpriteComponent>(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));

	m_TestCamera = m_ActiveScene->CreateEntity("Test Camera");
	m_TestCamera.AddComponent<Illusion::CameraComponent>();

	m_KeyboardTracker = m_ActiveScene->CreateEntity("Keyboard Tracker");
	m_KeyboardTracker.AddComponent<Illusion::NativeScriptComponent>().Bind<Tracker>();
}

void GameLayer::OnUpdate(Illusion::Timestep timestep)
{
	m_ActiveScene->OnUpdate(timestep);
}

void GameLayer::OnEvent(Illusion::Event& event)
{
	m_ActiveScene->OnEvent(event);
}

void GameLayer::OnDetach()
{

}

void GameLayer::OnImGuiRender()
{

}