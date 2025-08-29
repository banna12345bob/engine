#pragma once

namespace Engine {

	struct BoundingBox {
		BoundingBox() : x(0), y(0), width(0), height(0) {}
		BoundingBox(float x, float y, float width, float height) : x(x), y(y), width(width), height(height) {}
		float x = 0, y = 0, width = 0, height = 0;

		float left() { return x; }
		float right() { return x + width; }
		float top() { return y + height; }
		float bottom() { return y; }

		glm::vec2 position() {
			return glm::vec2(x, y);
		}
		glm::vec2 size() {
			return glm::vec2(width, height);
		}

		// Little bit of tweaking because we are working with the slightly inaccurate floats
		bool Intersect(BoundingBox other) {
			return left() < other.right() && right() > other.left() && bottom() < other.top() && top() > other.bottom();
		}
	};
}