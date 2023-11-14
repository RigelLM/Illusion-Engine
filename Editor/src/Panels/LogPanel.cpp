#include "LogPanel.h"

#include <Engine/Core/ECS/Components.h>
#include "../StringDataComponent.h"

namespace Illusion
{
	LogPanel::LogPanel()
	{
		ScrollToBottom = false;
		Clear();
	}

	LogPanel::LogPanel(const Ref<Scene>& context)
	{
		ScrollToBottom = false;
		Clear();
		SetContext(context);
	}

	void LogPanel::SetContext(const Ref<Scene>& context)
	{
		m_Context = context;
	}

	void LogPanel::Clear()
	{
		Buf.clear();
		LineOffsets.clear();
		LineOffsets.push_back(0);
	}

	void LogPanel::OnUpdate()
	{
		auto view = m_Context->m_Registry.view<StringDataComponent>();
		for (auto entityID : view)
		{
			Entity entity = { entityID, m_Context.get() };
			auto& sdc = entity.GetComponent<StringDataComponent>();
			if (sdc.NewData)
			{
				AddLog("[%05d] [%.1f] INFO: %s\n", ImGui::GetFrameCount(), ImGui::GetTime(), sdc.Data.c_str());
				sdc.NewData = false;
			}
		}
	}

	void LogPanel::AddLog(const char* fmt, ...)
	{
		int old_size = Buf.size();
		va_list args;
		va_start(args, fmt);
		Buf.appendfv(fmt, args);
		va_end(args);
		for (int new_size = Buf.size(); old_size < new_size; old_size++)
			if (Buf[old_size] == '\n')
				LineOffsets.push_back(old_size + 1);
		ScrollToBottom = true;
	}

	void LogPanel::OnImGuiRender()
	{
		ImGui::Begin("Log");

		if (ImGui::Button("Clear")) Clear();
		ImGui::SameLine();
		Filter.Draw("Filter", -100.0f);
		ImGui::Separator();
		ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
		const char* buf = Buf.begin();
		const char* buf_end = Buf.end();
		if (Filter.IsActive())
		{
			for (int line_no = 0; line_no < LineOffsets.Size; line_no++)
			{
				const char* line_start = buf + LineOffsets[line_no];
				const char* line_end = (line_no + 1 < LineOffsets.Size) ? (buf + LineOffsets[line_no + 1] - 1) : buf_end;
				if (Filter.PassFilter(line_start, line_end))
					ImGui::TextUnformatted(line_start, line_end);
			}
		}
		else
		{
			ImGuiListClipper clipper;
			clipper.Begin(LineOffsets.Size);
			while (clipper.Step())
			{
				for (int line_no = clipper.DisplayStart; line_no < clipper.DisplayEnd; line_no++)
				{
					const char* line_start = buf + LineOffsets[line_no];
					const char* line_end = (line_no + 1 < LineOffsets.Size) ? (buf + LineOffsets[line_no + 1] - 1) : buf_end;
					ImGui::TextUnformatted(line_start, line_end);
				}
			}
			clipper.End();
		}
		ImGui::PopStyleVar();

		if (ScrollToBottom)
			ImGui::SetScrollHereY(1.0f);
		ScrollToBottom = false;
		ImGui::EndChild();

		ImGui::End();
	}
}
