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
		ImGui::Begin("Scene Debugger");
		for (auto it = m_Scene.m_Entities.begin(); it != m_Scene.m_Entities.end(); it++)
		{
			if (ImGui::TreeNode(it->second->name.c_str()))
			{
				ImGui::Begin(it->second->name.c_str());
				float pos[3] = { it->second->GetTransform()->position.x, it->second->GetTransform()->position.y, it->second->GetTransform()->position.z };
				ImGui::DragFloat3("pos", pos);
				it->second->GetTransform()->position.x = pos[0];
				it->second->GetTransform()->position.y = pos[1];
				it->second->GetTransform()->position.z = pos[2];
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
