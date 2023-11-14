#pragma once

#include "imgui/imgui.h"

#include <Engine.h>

namespace Illusion
{
	class LogPanel
	{
	public:
		LogPanel();
		LogPanel(const Ref<Scene>& context);

		void SetContext(const Ref<Scene>& context);

		void OnUpdate();


		void OnImGuiRender();

	private:
		void Clear();

		void AddLog(const char* fmt, ...);
	private:
		Ref<Scene> m_Context;

		bool NewLog = false;

		ImGuiTextBuffer     Buf;
		ImGuiTextFilter     Filter;
		ImVector<int>       LineOffsets;
		bool                ScrollToBottom;
	};
}
