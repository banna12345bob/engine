#pragma once

#include "engine/core/Layer.h"
#include "engine/scene/Scene.h"

namespace Engine {

	class SceneDebugger : public Layer
	{
	public:
		SceneDebugger(Scene& scene);
		~SceneDebugger() = default;

		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& event) override;
	private:
		bool ShowWindow(KeyPressedEvent& e);

	private:
		bool m_ShowWindow = false;
		Scene& m_Scene;
	};
}

