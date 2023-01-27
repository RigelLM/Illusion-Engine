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

	// Initialize the particle system with two emitters
	pSys.AddEmitter(&emitter);
	pSys.AddEmitter(&emitter2);

	// Initialize the properties for each emitter
	prop.ColorBegin = { 255 / 255.0f, 255 / 255.0f, 0 / 255.0f, 1.0f };
	prop.ColorEnd = { 0 / 255.0f, 255 / 255.0f, 0 / 255.0f, 1.0f };
	prop.SizeBegin = 0.5f, prop.SizeVariation = 0.3f, prop.SizeEnd = 0.0f;
	prop.LifeTime = 1.0f;
	prop.Velocity = { 0.0f, 0.0f };
	prop.VelocityVariation = { 1.0f, 1.0f };
	prop.Position = { 0.0f, 0.0f };
	prop.Scale = 0.2f;

	prop2.ColorBegin = { 254 / 255.0f, 0 / 255.0f, 0 / 255.0f, 1.0f };
	prop2.ColorEnd = { 0 / 255.0f, 0 / 255.0f, 255 / 255.0f, 1.0f };
	prop2.SizeBegin = 0.5f, prop2.SizeVariation = 0.3f, prop2.SizeEnd = 0.0f;
	prop2.LifeTime = 1.0f;
	prop2.Velocity = { 0.0f, 0.0f };
	prop2.VelocityVariation = { 1.0f, 1.0f };
	prop2.Position = { 0.0f, 0.0f };
	prop2.Scale = 0.5f;
}

void TestLayer::OnDetach()
{

}

void TestLayer::OnUpdate(Illusion::Timestep timestep)
{

	// Update the camera
	m_CameraController.OnUpdate(timestep);

	// Update the properties for each emitter
	if (Illusion::Input::IsMouseButtonPressed(ILLUSION_MOUSE_BUTTON_LEFT))
	{
		// Figure out the position of the mouse cursor
		auto [x, y] = Illusion::Input::GetMousePosition();
		auto width = Illusion::Application::Get().GetWindow().GetWidth();
		auto height = Illusion::Application::Get().GetWindow().GetHeight();

		auto bounds = m_CameraController.GetBounds();
		auto pos = m_CameraController.GetCamera().GetPosition();
		x = (x / width) * bounds.GetWidth() - bounds.GetWidth() * 0.5f;
		y = bounds.GetHeight() * 0.5f - (y / height) * bounds.GetHeight();
		prop.Position = { x + pos.x, y + pos.y };
		prop2.Position = { x + pos.x + 0.8f, y + pos.y };

		// Assign it to the position of the emitter
		emitter.Configure(prop);
		emitter2.Configure(prop2);

		// Emit 5 particles at once
		//for (int i = 0; i < 5; i++)
		pSys.Emit();
	}

	// Update the particle system
	pSys.OnUpdate(timestep);

	// Render

	// Set the clear color
	// Clear the color buffer with the clear color
	Illusion::RenderCommand::Clear({ 0.0f, 0.0f, 0.0f, 1.0 });
	Illusion::Renderer2D::BeginScene(m_CameraController.GetCamera());
	pSys.OnRender();
	Illusion::Renderer2D::DrawQuad({ -1.0f,  0.0f }, { 0.8f, 0.8f }, m_Color);
	Illusion::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.5f }, m_Color);
	Illusion::Renderer2D::DrawRotatedQuad({ 0.0f,  0.0f, -0.1f }, glm::radians(45.0f), { 1.0f, 1.0f }, m_Texture);
	Illusion::Renderer2D::EndScene();
}

void TestLayer::OnImGuiRender()
{
	// Expose the color and lifetime of particles to ImGui
	ImGui::Begin("Settings1");
	ImGui::ColorEdit4("Birth Color", glm::value_ptr(prop.ColorBegin));
	ImGui::ColorEdit4("Death Color", glm::value_ptr(prop.ColorEnd));
	ImGui::DragFloat("Life Time", &prop.LifeTime, 0.1f, 0.0f, 1000.0f);
	ImGui::End();

	ImGui::Begin("Settings2");
	ImGui::ColorEdit4("Birth Color", glm::value_ptr(prop2.ColorBegin));
	ImGui::ColorEdit4("Death Color", glm::value_ptr(prop2.ColorEnd));
	ImGui::DragFloat("Life Time", &prop2.LifeTime, 0.1f, 0.0f, 1000.0f);
	ImGui::End();
}

void TestLayer::OnEvent(Illusion::Event& event)
{
	m_CameraController.OnEvent(event);
}