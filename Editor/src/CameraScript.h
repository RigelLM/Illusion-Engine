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
		auto& transform = GetComponent<Illusion::TransformComponent>().Transform;

		float speed = 5.0f;
		if (Illusion::Input::IsKeyPressed(Illusion::Key::Left))
			transform[3][0] -= speed * ts;
		else if (Illusion::Input::IsKeyPressed(Illusion::Key::Right))
			transform[3][0] += speed * ts;
		if (Illusion::Input::IsKeyPressed(Illusion::Key::Up))
			transform[3][1] += speed * ts;
		else if (Illusion::Input::IsKeyPressed(Illusion::Key::Down))
			transform[3][1] -= speed * ts;

		cam.SetPosition(transform[3]);
	}

	void OnEvent(Illusion::Event& e)
	{	}
};