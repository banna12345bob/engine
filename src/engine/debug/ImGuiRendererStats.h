#pragma once

#include "engine/debug/Instrumentor.h"
#include "engine/core/Layer.h"
#include "engine/events/AllEvents.h"

namespace Engine {

	class ImGuiRendererStats : public Layer
	{
	public:
		ImGuiRendererStats();

		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& event) override;
	private:
		bool ShowWindow(KeyPressedEvent& e);

	private:
		bool m_ShowWindow = false;
	};

}

