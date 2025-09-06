#include "Components.h"

#include <imgui.h>

namespace Engine {

	std::string ComponentToString(Components component)
	{
		switch (component) {
		case Transform:
			return std::string("Tranform");
		case SpriteRenderer:
			return std::string("SpriteRenderer");
		case Velocity:
			return std::string("Velocity");
		default:
			return std::string("Error converting component to string");
		}
	}

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

		// TODO: Probably just use the window file dialogue to select the file
		// I can't be bothered doing this now though
		if (ImGui::Button("Select Texture"))
			ImGui::OpenPopup("File selector");

		if (ImGui::BeginPopup("File selector")) {
			ImGui::Text("TODO: Open file dialogue");
			ImGui::EndPopup();
		}

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