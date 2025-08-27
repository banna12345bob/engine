#pragma once

namespace Engine {

	struct BoundingBox {
		BoundingBox() : x(0), y(0), width(0), height(0) {}
		BoundingBox(float x, float y, float width, float height) : x(x), y(y), width(width), height(height) {}
		float x = 0, y = 0, width = 0, height = 0;
	};
}