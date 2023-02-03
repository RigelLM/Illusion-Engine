#pragma once

#include <Engine.h>

#include "Level.h"

class GameLayer : public Illusion::Layer
{
public:
	GameLayer();
	virtual ~GameLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Illusion::Timestep timestep) override;
	void OnEvent(Illusion::Event& event) override;

	bool OnMouseButtonPressed(Illusion::MouseButtonPressedEvent& e);
	bool OnWindowResize(Illusion::WindowResizeEvent& e);

private:
	void CreateCamera(uint32_t width, uint32_t height);

private:
	Illusion::Scope<Illusion::Camera> m_Camera;

	Level m_Level;

	float m_Time = 0.0f;
	bool m_Blink = false;

	enum class GameState
	{
		Play = 0, MainMenu = 1, GameOver = 2
	};

	GameState m_State = GameState::MainMenu;

};

