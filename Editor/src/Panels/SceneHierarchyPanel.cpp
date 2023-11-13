#include "SceneHierarchyPanel.h"

#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>

#include <Engine/Core/ECS/Components.h>

namespace Illusion
{

	SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene>& context)
	{
		SetContext(context);
	}

	void SceneHierarchyPanel::SetContext(const Ref<Scene>& context)
	{
		m_Context = context;
	}

	void SceneHierarchyPanel::OnImGuiRender()
	{
		ImGui::Begin("Scene Hierarchy");
		auto view = m_Context->m_Registry.view<TagComponent>();
		for (auto entityID : view)
		{
			Entity entity = { entityID, m_Context.get() };
			DrawEntityNode(entity);
		}

		if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
			m_SelectionContext = {};
		ImGui::End();

		ImGui::Begin("Properties");
		if (m_SelectionContext)
			DrawComponents(m_SelectionContext);
		ImGui::End();
	}

	void SceneHierarchyPanel::DrawEntityNode(Entity entity)
	{
		auto& tag = entity.GetComponent<TagComponent>().Tag;

		ImGuiTreeNodeFlags flags = ((m_SelectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;

		bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tag.c_str());
		if (ImGui::IsItemClicked())
		{
			m_SelectionContext = entity;
		}

		if (opened)
		{
			ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
			bool opened = ImGui::TreeNodeEx((void*)9817239, flags, tag.c_str());
			if (opened)
				ImGui::TreePop();
			ImGui::TreePop();
		}
	}

	void SceneHierarchyPanel::DrawComponents(Entity entity)
	{
		if (entity.HasComponent<TagComponent>())
		{
			auto& tag = entity.GetComponent<TagComponent>().Tag;

			char buffer[256];
			memset(buffer, 0, sizeof(buffer));
			strcpy_s(buffer, sizeof(buffer), tag.c_str());
			if (ImGui::InputText("Tag", buffer, sizeof(buffer)))
			{
				tag = std::string(buffer);
			}
		}

		if (entity.HasComponent<TransformComponent>())
		{
			if (ImGui::TreeNodeEx((void*)typeid(TransformComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Transform"))
			{
				auto& transform = entity.GetComponent<TransformComponent>().Transform;
				ImGui::DragFloat3("Position", glm::value_ptr(transform[3]), 0.1f);

				ImGui::TreePop();
			}
		}

		if (entity.HasComponent<CameraComponent>())
		{
			if (ImGui::TreeNodeEx((void*)typeid(CameraComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Camera"))
			{
				auto& cc = entity.GetComponent<CameraComponent>();
				auto& c = cc.camera;

				// ImGui::Checkbox("Primary", &cc.Primary);

				const char* projectionTypeStrings[] = { "Perspective", "Orthographic" };
				const char* currentProjectionTypeString = projectionTypeStrings[(int)c.GetType()];
				if (ImGui::BeginCombo("Projection", currentProjectionTypeString))
				{
					for (int i = 0; i < 2; i++)
					{
						bool isSelected = currentProjectionTypeString == projectionTypeStrings[i];
						if (ImGui::Selectable(projectionTypeStrings[i], isSelected))
						{
							currentProjectionTypeString = projectionTypeStrings[i];
							c.SetType((Camera::CameraType)i);
						}

						if (isSelected)
							ImGui::SetItemDefaultFocus();
					}

					ImGui::EndCombo();
				}

				if (c.GetType() == Camera::CameraType::Perspective)
				{
					float perspectiveVerticalFov = glm::degrees(c.GetPerspectiveFOV());
					if (ImGui::DragFloat("FOV", &perspectiveVerticalFov))
						c.SetPerspectiveFOV(glm::radians(perspectiveVerticalFov));

					float perspectiveNear = c.GetPerspectiveNear();
					if (ImGui::DragFloat("Near", &perspectiveNear))
						c.SetPerspectiveNear(perspectiveNear);

					float perspectiveFar = c.GetPerspectiveFar();
					if (ImGui::DragFloat("Far", &perspectiveFar))
						c.SetPerspectiveFar(perspectiveFar);
				}
				else
				{
					float orthoSize = c.GetOrthoZoomLevel();
					if (ImGui::DragFloat("Size", &orthoSize))
						c.SetOrthoZoomLevel(orthoSize);

					float orthoNear = c.GetOrthoNear();
					if (ImGui::DragFloat("Near", &orthoNear))
						c.SetOrthoNear(orthoNear);

					float orthoFar = c.GetOrthoFar();
					if (ImGui::DragFloat("Far", &orthoFar))
						c.SetOrthoFar(orthoFar);
				}

				ImGui::TreePop();
			}
		}

		if (entity.HasComponent<SpriteComponent>())
		{
			if (ImGui::TreeNodeEx((void*)typeid(SpriteComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Sprite"))
			{
				auto& sc = entity.GetComponent<SpriteComponent>();
				ImGui::ColorEdit4("Color", glm::value_ptr(sc.Color));

				ImGui::TreePop();
			}
		}
	}

}
