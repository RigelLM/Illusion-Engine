#pragma once

#include <Engine.h>

class GameLayer : public Illusion::Layer
{
public:
	GameLayer();
	virtual ~GameLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(Illusion::Timestep timestep) override;
	virtual void OnEvent(Illusion::Event& event) override;
	virtual void OnImGuiRender() override;

private:
	Illusion::Ref<Illusion::Scene> m_ActiveScene;

	Illusion::Entity m_SqureEntity;
	Illusion::Entity m_TestCamera;
	Illusion::Entity m_KeyboardTracker;

};


