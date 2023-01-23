#include "TestLayer.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

TestLayer::TestLayer()
	:Layer("TestLayer"), m_CameraController(2560.0f / 1440.0f, true)
{

}

void TestLayer::OnAttach()
{
	m_Texture.reset(new Illusion::Texture2D("assets/textures/CheckerBoard.png"));
}

void TestLayer::OnDetach()
{

}

void TestLayer::OnUpdate(Illusion::Timestep timestep)
{
	// Updata
	m_CameraController.OnUpdate(timestep);

	// Render

	// Set the clear color
	// Clear the color buffer with the clear color
	Illusion::RenderCommand::Clear({ 0.0f, 0.0f, 0.0f, 1.0 });
	Illusion::Renderer2D::BeginScene(m_CameraController.GetCamera());
	Illusion::Renderer2D::DrawQuad({ -1.0f,  0.0f }, { 0.8f, 0.8f }, m_Color);
	Illusion::Renderer2D::DrawQuad({  0.5f, -0.5f }, { 0.5f, 0.7f }, m_Color);
	Illusion::Renderer2D::DrawRotatedQuad({ 0.0f,  0.0f, -0.1f }, glm::radians(45.0f), { 1.0f, 1.0f }, m_Texture);
	Illusion::Renderer2D::EndScene();
}

void TestLayer::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("m_Color", glm::value_ptr(m_Color));
	ImGui::End();
}

void TestLayer::OnEvent(Illusion::Event& event)
{
	m_CameraController.OnEvent(event);
}