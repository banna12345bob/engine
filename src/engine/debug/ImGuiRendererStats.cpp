#include "ImGuiRendererStats.h"

#include <imgui.h>

#include "engine/renderer/Renderer2D.h"

namespace Engine {

	ImGuiRendererStats::ImGuiRendererStats()
	{
	}

	void ImGuiRendererStats::renderImGUILayer()
	{
		if (!m_ShowWindow)
			return;

		ImGui::Begin("Renderer stats", &m_ShowWindow);
			auto stats = Engine::Renderer2D::GetStats();
			ImGui::Text("Renderer2D Stats:");
			ImGui::Text("Draw Calls: %d", stats.DrawCalls);
			ImGui::Text("Quads: %d", stats.squareCount);
			ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
			ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
		ImGui::End();
	}


}
