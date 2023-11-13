#include <Engine.h>

class Tracker : public Illusion::Script
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
	}

	bool OnKeyPressed(Illusion::KeyPressedEvent& e)
	{
		auto& tag = GetComponent<Illusion::TagComponent>().Tag;
		std::cout << tag << ": " << e.GetKeyCode() << std::endl;
		return false;
	}
};