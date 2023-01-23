/*
 * ========================== Game.cpp ========================
 *                          -- ils --
 *                                        CREATE -- 2023.01.12
 *                                        MODIFY --
 * ----------------------------------------------------------
 * Game class
 * Only responsible for:
 *					assigning things that have to be updated
 *					assigning the order of update
 *					provide the implementation for the creation of the app
 * ----------------------------
 */

#include <Engine.h>
 //--------------------Entry point for the application--------------------
#include <Engine/Core/EntryPoint.h>

#include "TestLayer.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class GameLayer : public Illusion::Layer
{
public:
	GameLayer()
		: Layer("Game"), m_CameraController(2560.0f / 1440.0f, true)
	{
		// Set up Vertices
		float squarevertices[5 * 4] =
		{
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
		};

		// Create VAO
		m_SquareVAO.reset(new Illusion::VAO());

		// Create VBO with vertices data
		Illusion::Ref<Illusion::VBO> squareVBO;
		squareVBO.reset(new Illusion::VBO(squarevertices, sizeof(squarevertices)));

		// Set up the layout of the vertices data for every vertex
		Illusion::VBODataLayout squarelayout = {
			{ Illusion::VertexDataType::Float3, "a_Position"},
			{ Illusion::VertexDataType::Float2, "a_TexCord"}
		};

		squareVBO->SetDataLayout(squarelayout);

		m_SquareVAO->AddVBO(squareVBO);

		// Set up indices
		unsigned int squareindices[6] =
		{
			0,1,2,2,3,0
		};

		// Create IBO/EBO
		Illusion::Ref<Illusion::IBO> squareIBO;
		squareIBO.reset(new Illusion::IBO(squareindices, sizeof(squareindices) / sizeof(uint32_t)));

		// Bind IBO with VAO
		m_SquareVAO->SetIBO(squareIBO);

		// Create the shader program
		Illusion::ResourceManager::LoadShader("assets/shaders/TextureShader.glsl", "TextureShader");

		m_Texture.reset(new Illusion::Texture2D("assets/textures/CheckerBoard.png"));

		Illusion::ResourceManager::GetShader("TextureShader")->Bind();
		Illusion::ResourceManager::GetShader("TextureShader")->UploadUniformInt("u_Texture", 0);

	}

	void OnUpdate(Illusion::Timestep timestep) override
	{
		//ENGINE_CLIENT_TRACE("Delta time: {0}; FPS: {1}", timestep.GetSeconds(), (int)1.0f/timestep.GetSeconds());

		// Update
		m_CameraController.OnUpdate(timestep);


		//Render

		// Set the clear color
		// Clear the color buffer with the clear color
		Illusion::RenderCommand::Clear({ 0.1f, 0.1f, 0.1f, 1.0 });

		Illusion::Renderer::BeginScene(m_CameraController.GetCamera());
		{
			m_Texture->Bind();
			// Draw Call of the main application
			Illusion::Renderer::Submit(Illusion::ResourceManager::GetShader("TextureShader"), m_SquareVAO, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		}
		Illusion::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		//ImGui::Begin("Settings");
		//ImGui::ColorEdit3("m_SquareColor", glm::value_ptr(m_SquareColor));
		//ImGui::End();
	}

	void OnEvent(Illusion::Event& event) override
	{
		m_CameraController.OnEvent(event);
	}

private:
	Illusion::Ref<Illusion::VAO> m_SquareVAO;
	Illusion::Ref<Illusion::Texture2D> m_Texture;

	Illusion::CameraController m_CameraController;
};

class Game : public Illusion::Application
{

public:
	Game()
	{
		//PushLayer(new GameLayer());
		PushLayer(new TestLayer());
	}

	~Game() {}

private:

};

//The Creation function for the Game Application
Illusion::Application* Illusion::CreateApplication()
{
	return new Game();
}