#include <Engine.h>

#include "Panels/LogPanel.h"
#include "StringDataComponent.h"

class Logger : public Illusion::Script
{
public:
	void OnCreate()
	{
	}

	void OnDestroy()
	{
	}

	void OnUpdate(Illusion::Timestep ts)
	{
	}

	void OnEvent(Illusion::Event& e)
	{
		Illusion::EventDispatcher dispatcher(e);
		dispatcher.Dispatch<Illusion::KeyPressedEvent>(ENGINE_BIND_EVENT_FN(OnKeyPressed));
		dispatcher.Dispatch<Illusion::MouseButtonPressedEvent>(ENGINE_BIND_EVENT_FN(OnMousePressed));
	}

	bool OnMousePressed(Illusion::MouseButtonPressedEvent& e)
	{
		auto& sdc = GetComponent<StringDataComponent>();
		sdc.Data = "Mouse Button: ";
		sdc.Data.append(std::to_string(e.GetMouseButton()));
		sdc.Data.append(" pressed");

		sdc.NewData = true;

		return false;
	}

	bool OnKeyPressed(Illusion::KeyPressedEvent& e)
	{
		auto& sdc = GetComponent<StringDataComponent>();
		sdc.Data = "Key: ";
		sdc.Data.append(std::to_string(e.GetKeyCode()));
		sdc.Data.append(" pressed");
		
		sdc.NewData = true;

		return false;
	}
};