#include <Engine.h>
 //--------------------Entry point for the application--------------------
#include <Engine/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Illusion
{
	class Game : public Application
	{

	public:
		Game()
		{
			PushLayer(new EditorLayer());
		}

		~Game() {}

	private:

	};

	//The Creation function for the Game Application
	Application* CreateApplication()
	{
		return new Game();
	}
}

