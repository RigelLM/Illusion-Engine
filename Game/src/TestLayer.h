#pragma once

#include <Engine.h>

class TestLayer : public Illusion::Layer
{
public:
	TestLayer();
	virtual ~TestLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Illusion::Timestep timestep) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Illusion::Event& event) override;

private:
	Illusion::CameraController m_CameraController;

	// Temp
	Illusion::Ref<Illusion::VAO> m_VAO;

	Illusion::Ref<Illusion::Texture2D> m_Texture;

	glm::vec4 m_Color = { 0.2f, 0.3f, 0.8f, 1.0f };

};

