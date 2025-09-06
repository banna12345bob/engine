#include "SceneDebugger.h"

#include "Instrumentor.h"
#include "engine/core/Keycodes.h"

#include <imgui.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

namespace Engine {

	SceneDebugger::SceneDebugger(Scene& scene)
		: Layer("SceneDebugger"), m_Scene(scene)
	{
	}
	
	void SceneDebugger::OnImGuiRender()
	{
		EG_PROFILE_FUNCTION();
		if (!this->m_ShowWindow)
			return;
		ImGui::Begin("Scene Debugger", &m_ShowWindow);
		for (auto it = m_Scene.m_Entities.begin(); it != m_Scene.m_Entities.end(); it++)
		{
			if (ImGui::TreeNode(it->second->name.c_str()))
			{
				ImGui::Begin(it->second->name.c_str());
				for (auto component = it->second->GetComponents()->begin(); component != it->second->GetComponents()->end(); component++)
				{
					if (ImGui::TreeNode(ComponentToString(component->first).c_str()))
					{
						component->second->ImGuiRender();
						ImGui::TreePop();
					}
				}
				ImGui::Checkbox("Hide", &it->second->hide);
				if (ImGui::Button("Delete"))
					m_Scene.RemoveEntity(it->first);
				ImGui::End();

				ImGui::TreePop();
			}

			//ImGui::BeginPopup(it->second->name.c_str());
		}
		ImGui::End();
	}

	void SceneDebugger::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<KeyPressedEvent>(EG_BIND_EVENT_FN(SceneDebugger::ShowWindow));
	}

	bool SceneDebugger::ShowWindow(KeyPressedEvent& e)
	{
		if (e.GetKeyCode() == EG_KEY_F3 && e.GetRepeatCount() == 0) {
			m_ShowWindow = !m_ShowWindow;
			return true;
		}
		return false;
	}
}
