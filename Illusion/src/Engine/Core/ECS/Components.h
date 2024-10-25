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
		glm::vec3 Position = { 0.0f,0.0f,0.0f };
		glm::vec3 Rotation = { 0.0f,0.0f,0.0f };
		glm::vec3 Scale = { 1.0f,1.0f,1.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::vec3& position)
			:Position(position) {}

		glm::mat4 GetTransform() const
		{
			glm::mat4 translation = glm::translate(glm::mat4(1.0f), Position);
			glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), Rotation.x, { 1.0f, 0.0f, 0.0f })
				* glm::rotate(glm::mat4(1.0f), Rotation.y, { 0.0f, 1.0f, 0.0f })
				* glm::rotate(glm::mat4(1.0f), Rotation.z, { 0.0f, 0.0f, 1.0f });
			glm::mat4 scale = glm::scale(glm::mat4(1.0f), Scale);

			return translation * rotation * scale;
		}

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

		bool Primary = false;

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
	};
}
