/*****************************************************************//**
 * \file   Scene.h
 * \brief  Scene class that represents the level of the game
 *
 * \author Mian Li
 * \date   October 2024
 *********************************************************************/

#include "pch.h"
#include "Scene.h"

#include <Engine/Render/Renderer/Renderer2D.h>

#include "Entity.h"

#include "Components.h"

namespace Illusion
{
	Scene::Scene()
	{
		entt::entity ent = m_Registry.create();
	}

	Scene::~Scene()
	{

	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<TransformComponent>();

		auto& tag = entity.AddComponent<TagComponent>(name);
		tag.Tag = name.empty() ? "Entity" : name;

		return entity;
	}

	void Scene::DestroyEntity(Entity entity)
	{
		m_Registry.destroy(entity);
	}

	void Scene::OnUpdate(Timestep ts)
	{
		// Update scripts
		{
			m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc)
				{
					if (!nsc.ScriptInstance)
					{
						nsc.InstantiateFunction();
						nsc.ScriptInstance->m_Entity = Entity{ entity, this };

						if (nsc.OnCreateFunction)
							nsc.OnCreateFunction(nsc.ScriptInstance);
					}

					if (nsc.OnUpdateFunction)
						nsc.OnUpdateFunction(nsc.ScriptInstance, ts);
				});
		}

		// Get primary camera and its viewprojection matrix
		glm::mat4* vp = nullptr;
		glm::mat4 temp;
		auto view = m_Registry.view<CameraComponent>();
		for (auto entity : view)
		{
			auto& CamComp = view.get<CameraComponent>(entity);
			if (CamComp.Primary)
			{
				temp = CamComp.camera.GetViewProjection();
				vp = &temp;
				break;
			}
		}

		// Rendering
		Illusion::Renderer2D::Clear({ 0.0f, 0.0f, 0.0f });

		if (vp)
		{
			Illusion::Renderer2D::BeginScene(*vp);

			auto view = m_Registry.view<TransformComponent, SpriteComponent>();
			for (auto entity : view)
			{
				auto [transform, sprite] = view.get<TransformComponent, SpriteComponent>(entity);
				Renderer2D::DrawQuad(transform.GetTransform(), sprite.Color);
			}

			Illusion::Renderer2D::EndScene();
		}
	}

	void Scene::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowResizeEvent>(ENGINE_BIND_EVENT_FN(OnWindowResized));

		// Update scripts
		m_Registry.view<NativeScriptComponent>().each([&](auto entity, auto& nsc)
			{
				if (!nsc.ScriptInstance)
				{
					nsc.InstantiateFunction();
					nsc.ScriptInstance->m_Entity = Entity{ entity, this };

					if (nsc.OnCreateFunction)
						nsc.OnCreateFunction(nsc.ScriptInstance);
				}

				if (nsc.OnEventFunction)
					nsc.OnEventFunction(nsc.ScriptInstance, e);

			});
	}

	bool Scene::OnWindowResized(WindowResizeEvent& e)
	{
		float ratio = (float)e.GetWidth() / (float)e.GetHeight();
		// m_AspectRatio = ratio;
		auto view = m_Registry.view<CameraComponent>();
		for (auto entity : view)
		{
			auto& Cam = view.get<CameraComponent>(entity).camera;
			Cam.SetAspectRatio(ratio);
		}
		return false;
	}

}
