#include <Engine.h>

class CameraController : public Illusion::Script
{
public:
	void OnCreate()
	{	}

	void OnDestroy()
	{	}

	void OnUpdate(Illusion::Timestep ts)
	{
		auto& cam = GetComponent<Illusion::CameraComponent>().camera;
		auto& position = GetComponent<Illusion::TransformComponent>().Position;

		float speed = 5.0f;
		if (Illusion::Input::IsKeyPressed(Illusion::Key::Left))
			position.x -= speed * ts;
		else if (Illusion::Input::IsKeyPressed(Illusion::Key::Right))
			position.x += speed * ts;
		if (Illusion::Input::IsKeyPressed(Illusion::Key::Up))
			position.y += speed * ts;
		else if (Illusion::Input::IsKeyPressed(Illusion::Key::Down))
			position.y -= speed * ts;

		cam.SetPosition(position);
	}

	void OnEvent(Illusion::Event& e)
	{	}
};