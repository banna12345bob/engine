#include "ImGuiRendererStats.h"

#include <imgui.h>

#include "engine/renderer/Renderer2D.h"
#include "engine/core/Keycodes.h"

namespace Engine {

	ImGuiRendererStats::ImGuiRendererStats()
		: Layer("RenderStats")
	{
	}

	void ImGuiRendererStats::OnImGuiRender()
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

	void ImGuiRendererStats::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<KeyPressedEvent>(EG_BIND_EVENT_FN(ImGuiRendererStats::ShowWindow));
	}

	bool ImGuiRendererStats::ShowWindow(KeyPressedEvent& e)
	{
		if (e.GetKeyCode() == EG_KEY_F2) {
			m_ShowWindow = !m_ShowWindow;
			return true;
		}
		return false;
	}

}
