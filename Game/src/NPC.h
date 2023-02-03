#pragma once

#include <Engine.h>

class NPC
{
public:

	NPC();
	
	void LoadAssets();

	void OnUpdate(Illusion::Timestep ts);
	void OnRender();

	void OnEvent(Illusion::Event& e);

	const glm::vec2& GetPosition() const { return m_Position; }

	bool OnKeyPressed(Illusion::KeyPressedEvent& e);

private:

	glm::vec2 m_Position = { 0.0f, 0.0f };
};

