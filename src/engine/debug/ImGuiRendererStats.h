#pragma once

#include "engine/debug/Instrumentor.h"
#include "engine/ImGui/ImGuiLayer.h"

namespace Engine {

	class ImGuiRendererStats : public ImGuiLayer
	{
	public:
		ImGuiRendererStats();

		virtual void renderImGUILayer() override;
	};

}

