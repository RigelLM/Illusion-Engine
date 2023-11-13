#pragma once

#include "Script.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <Engine/Event/Events.h>
#include <Engine/Render/CameraSystem/Camera.h>


namespace Illusion
{
	struct TagComponent
	{
		std::string Tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag)
			:Tag(tag) {}
	};

	struct TransformComponent
	{
		// Transform matrix:
		// 
		// a11 a12 a13 a14
		// a21 a22 a23 a24
		// a31 a32 a33 a34
		// 0	0	0	1

		// (a14, a24, a34) is position (x, y, z)

		// | a11 a12 a13 |
		// | a21 a22 a23 |
		// | a31 a32 a33 | is rotations, scalings/reﬂections and shears

		glm::mat4 Transform{ 1.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::mat4& transform)
			:Transform(transform) {}

		operator glm::mat4& () { return Transform; }
		operator const glm::mat4& () const { return Transform; }

	};

	struct SpriteComponent
	{
		glm::vec4 Color{ 1.0f, 1.0f, 1.0f, 1.0f };

		SpriteComponent() = default;
		SpriteComponent(const SpriteComponent&) = default;
		SpriteComponent(const glm::vec4& color)
			:Color(color) {}
	};

	struct NativeScriptComponent
	{
		Script* ScriptInstance = nullptr;

		std::function<void()> InstantiateFunction;
		std::function<void()> DestroyInstanceFunction;

		std::function<void(Script*)> OnCreateFunction;
		std::function<void(Script*)> OnDestroyFunction;
		std::function<void(Script*, Timestep)> OnUpdateFunction;
		std::function<void(Script*, Event&)> OnEventFunction;

		template<typename T>
		void Bind()
		{
			InstantiateFunction = [&]() { ScriptInstance = new T(); };
			DestroyInstanceFunction = [&]() { delete (T*)ScriptInstance; ScriptInstance = nullptr; };

			OnCreateFunction = [](Script* instance) { ((T*)instance)->OnCreate(); };
			OnDestroyFunction = [](Script* instance) { ((T*)instance)->OnDestroy(); };
			OnUpdateFunction = [](Script* instance, Timestep ts) { ((T*)instance)->OnUpdate(ts); };
			OnEventFunction = [](Script* instance, Event& e) { ((T*)instance)->OnEvent(e); };
		}
	};

	struct CameraComponent
	{
		Camera camera;

		bool Primary = true;

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
	};
}
