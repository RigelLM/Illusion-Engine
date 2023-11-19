#include "SceneHierarchyPanel.h"

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include <glm/gtc/type_ptr.hpp>

#include <Engine/Core/ECS/Components.h>

#include "../CameraScript.h"

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

		// Right click on the blank space
		if (ImGui::BeginPopupContextWindow(0, 1))
		{
			if (ImGui::MenuItem("Create Empty Entity"))
				m_Context->CreateEntity("Empty Entity");

			ImGui::EndPopup();
		}

		ImGui::End();

		ImGui::Begin("Properties");
		if (m_SelectionContext)
		{
			DrawComponents(m_SelectionContext);

			if (ImGui::Button("Add Component"))
				ImGui::OpenPopup("Add Component");

			if (ImGui::BeginPopup("Add Component"))
			{
				if (ImGui::MenuItem("Camera"))
				{
					float windowWidth= static_cast<float>(Application::Get().GetWindow().GetWidth());
					float windowHeight = static_cast<float>(Application::Get().GetWindow().GetHeight());
					// Set aspect ratio of the camera component so it fits the current window
					m_SelectionContext.AddComponent<CameraComponent>(windowWidth / windowHeight);
					// m_SelectionContext.AddComponent<CameraComponent>();

					ImGui::CloseCurrentPopup();
				}

				if (ImGui::MenuItem("Sprite"))
				{
					m_SelectionContext.AddComponent<SpriteComponent>();
					ImGui::CloseCurrentPopup();
				}

				if (ImGui::MenuItem("Native Script"))
				{
					m_SelectionContext.AddComponent<NativeScriptComponent>().Bind<CameraController>();
					ImGui::CloseCurrentPopup();
				}

				ImGui::EndPopup();
			}

		}

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

		// Right click on the Entity
		// Defer the deletion of the entity
		bool EntityDeleted = false;
		if (ImGui::BeginPopupContextItem())
		{
			if (ImGui::MenuItem("Delete Entity"))
				EntityDeleted = true;

			ImGui::EndPopup();
		}

		if (opened)
		{
			ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
			bool opened = ImGui::TreeNodeEx((void*)9817239, flags, tag.c_str());
			if (opened)
				ImGui::TreePop();
			ImGui::TreePop();
		}

		// Defer the deletion of the entity
		if (EntityDeleted)
		{
			m_Context->DestroyEntity(entity);
			if (m_SelectionContext == entity)
				m_SelectionContext = {};
		}
	}

	static void DrawVec3Control(const std::string& label, glm::vec3& values, float resetValues = 0.0f, float columnWidth = 100.0f)
	{
		ImGuiIO& io = ImGui::GetIO();
		auto BoldFont = io.Fonts->Fonts[0];

		ImGui::PushID(label.c_str());

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

		{
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.25f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });

			ImGui::PushFont(BoldFont);
			if (ImGui::Button("X", buttonSize))
				values.x = resetValues;
			ImGui::PopFont();

			ImGui::PopStyleColor(3);
		}

		ImGui::SameLine();

		ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%0.2f");
		ImGui::PopItemWidth();

		ImGui::SameLine();

		{
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });

			ImGui::PushFont(BoldFont);
			if (ImGui::Button("Y", buttonSize))
				values.y = resetValues;
			ImGui::PopFont();

			ImGui::PopStyleColor(3);
		}

		ImGui::SameLine();

		ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%0.2f");
		ImGui::PopItemWidth();

		ImGui::SameLine();

		{
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });

			ImGui::PushFont(BoldFont);
			if (ImGui::Button("Z", buttonSize))
				values.z = resetValues;
			ImGui::PopFont();

			ImGui::PopStyleColor(3);
		}

		ImGui::SameLine();

		ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%0.2f");
		ImGui::PopItemWidth();

		ImGui::PopStyleVar();

		ImGui::Columns(1);

		ImGui::PopID();
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

		const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_AllowItemOverlap;

		if (entity.HasComponent<TransformComponent>())
		{
			if (ImGui::TreeNodeEx((void*)typeid(TransformComponent).hash_code(), treeNodeFlags, "Transform"))
			{
				auto& tc = entity.GetComponent<TransformComponent>();
				DrawVec3Control("Position", tc.Position);

				glm::vec3 r = glm::degrees(tc.Rotation);
				DrawVec3Control("Rotation", r);
				tc.Rotation = glm::radians(r);

				DrawVec3Control("Scale", tc.Scale, 1.0f);

				ImGui::TreePop();
			}
		}

		// can be deleted
		if (entity.HasComponent<CameraComponent>())
		{
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 });

			bool open = ImGui::TreeNodeEx((void*)typeid(CameraComponent).hash_code(), treeNodeFlags, "Camera");

			ImGui::SameLine(ImGui::GetWindowWidth() - 25.0f);

			bool removeComponent = false;
			if (ImGui::Button("+", ImVec2{ 20.0f,20.0f }))
				ImGui::OpenPopup("Component Settings");

			ImGui::PopStyleVar();

			if (ImGui::BeginPopup("Component Settings"))
			{
				if (ImGui::MenuItem("Remove"))
				{
					removeComponent = true;
					ImGui::CloseCurrentPopup();
				}

				ImGui::EndPopup();
			}

			if (open)
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

			// Defer the deletion
			if (removeComponent == true)
				entity.RemoveComponent<CameraComponent>();
		}
		// can be deleted
		if (entity.HasComponent<SpriteComponent>())
		{
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 });
			bool open = ImGui::TreeNodeEx((void*)typeid(SpriteComponent).hash_code(), treeNodeFlags, "Sprite");

			ImGui::SameLine(ImGui::GetWindowWidth() - 25.0f);

			bool removeComponent = false;
			if (ImGui::Button("+", ImVec2{ 20.0f,20.0f }))
				ImGui::OpenPopup("Component Settings");

			ImGui::PopStyleVar();

			if (ImGui::BeginPopup("Component Settings"))
			{
				if (ImGui::MenuItem("Remove"))
				{
					removeComponent = true;
					ImGui::CloseCurrentPopup();
				}

				ImGui::EndPopup();
			}

			if (open)
			{
				auto& sc = entity.GetComponent<SpriteComponent>();
				ImGui::ColorEdit4("Color", glm::value_ptr(sc.Color));

				ImGui::TreePop();
			}

			// Defer the deletion
			if (removeComponent == true)
				entity.RemoveComponent<SpriteComponent>();
		}
	}

}
