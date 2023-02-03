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

#include "GameLayer.h"

class Game : public Illusion::Application
{

public:
	Game()
	{
		//PushLayer(new GameLayer());
		PushLayer(new GameLayer());
	}

	~Game() {}

private:

};

//The Creation function for the Game Application
Illusion::Application* Illusion::CreateApplication()
{
	return new Game();
}