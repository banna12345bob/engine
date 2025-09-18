#include "Components.h"

#include <imgui.h>
#include <SDL3/SDL_dialog.h>
#include <filesystem>

namespace Engine {

	void TransformComponent::ImGuiRender() 
	{
		float tempPos[3] = { position.x, position.y, position.z };
		ImGui::DragFloat3("Position", tempPos);
		position.x = tempPos[0];
		position.y = tempPos[1];
		position.z = tempPos[2];

		ImGui::DragFloat("Rotation", &rotation, 1.f, -180.f, 180.f);

		float tempScale[2] = { scale.x, scale.y };
		ImGui::DragFloat2("Scale", tempScale);
		scale.x = tempScale[0];
		scale.y = tempScale[1];
	}

	void SpriteRendererComponent::ImGuiRender()
	{
		float tempColour[4] = { colour.r, colour.g, colour.b, colour.a };
		ImGui::ColorEdit4("Colour", tempColour);
		colour.r = tempColour[0];
		colour.g = tempColour[1];
		colour.b = tempColour[2];
		colour.a = tempColour[3];

		SDL_DialogFileFilter filter = {"PNG images",  "png"};

		if (ImGui::Button("Select Texture")) {			
			SDL_ShowOpenFileDialog([](void* userdata, const char* const* filelist, int filter)
				{
					if (!*filelist)
						return;
					SpriteRendererComponent* spriteRenderer = (SpriteRendererComponent*)userdata;
					spriteRenderer->filepath = *filelist;
				},
				this, nullptr, &filter, 1, (std::filesystem::current_path().string() + "\\assets\\").c_str(), false);
		}

		if (!filepath.empty() && (!texture || filepath != texture->getFilePath()))
			texture = Texture2D::Create(filepath);

		ImGui::DragFloat("Tiling Factor", &tilingFactor, 0.05f);
	}

	void VelocityComponent::ImGuiRender()
	{
		float tempVel[3] = { velocity.x, velocity.y, velocity.z };
		ImGui::DragFloat3("Velocity", tempVel);
		velocity.x = tempVel[0];
		velocity.y = tempVel[1];
		velocity.z = tempVel[2];

		ImGui::DragFloat("Rotational Velocity", &rotationVelocity);

		float tempScaleVel[2] = { scaleVelocity.x, scaleVelocity.y };
		ImGui::DragFloat2("Scaling Velocity", tempScaleVel);
		scaleVelocity.x = tempScaleVel[0];
		scaleVelocity.y = tempScaleVel[1];
	}
}