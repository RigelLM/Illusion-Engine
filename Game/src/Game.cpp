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