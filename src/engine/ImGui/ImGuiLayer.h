#pragma once

namespace Engine {

	class ImGuiLayer
	{
	public:
		virtual void renderImGUILayer() = 0;

		// Layer not shown by default
		bool m_ShowWindow = false;
	};

}