#pragma once

#include "engine/scene/Components.h"

#include <box2d/box2d.h>

namespace Engine {
	namespace Utils {

		b2BodyType RigidBodyTypeToBox2DType(RigidBody2DComponent::BodyType bodyType)
		{
			switch (bodyType) 
			{
			case RigidBody2DComponent::BodyType::Static: return b2_staticBody;
			case RigidBody2DComponent::BodyType::Dynamic: return b2_dynamicBody;
			case RigidBody2DComponent::BodyType::Kinematic: return b2_kinematicBody;
			}

			EG_CORE_ASSERT(false, "Unknown body type");
			return b2_staticBody;
		}

		RigidBody2DComponent::BodyType Box2DTypeToRigidBodyType(b2BodyType bodyType)
		{
			switch (bodyType) 
			{
			case b2_staticBody: return RigidBody2DComponent::BodyType::Static;
			case b2_dynamicBody: return RigidBody2DComponent::BodyType::Dynamic;
			case b2_kinematicBody: return RigidBody2DComponent::BodyType::Kinematic;
			}

			EG_CORE_ASSERT(false, "Unknown body type");
			return RigidBody2DComponent::BodyType::Static;
		}

	}
}