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

	Illusion::Ref<Illusion::Texture2D> m_Texture;

	Illusion::Ref<Illusion::SequenceAnimation> m_Animation;

	glm::vec4 m_Color = { 0.2f, 0.3f, 0.8f, 1.0f };

	Illusion::ParticleSystem pSys;
	Illusion::ParticleEmitter emitter;
	Illusion::ParticleEmitter emitter2;
	Illusion::ParticleProp prop;
	Illusion::ParticleProp prop2;

};

