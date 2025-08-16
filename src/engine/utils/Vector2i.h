#pragma once

#include <string>
#include <format>
#include <glm/glm.hpp>

#include "glm/vec2.hpp"

namespace Engine {

	struct Vector2i
	{
	public:
		constexpr Vector2i(int x = 0, int y = 0) : x(x), y(y) {}
		constexpr Vector2i(glm::vec2 v) : x(v.x), y(v.y) {}

		constexpr Vector2i operator*(int scalar) const {
			return { x * scalar, y * scalar };
		}
		constexpr Vector2i operator/(int scalar) const {
			return { x / scalar, y / scalar };
		}

		constexpr Vector2i& operator*=(int scalar) {
			x *= scalar;
			y *= scalar;
			return *this;
		}
		constexpr Vector2i& operator/=(int scalar) {
			x /= scalar;
			y /= scalar;
			return *this;
		}

		constexpr bool operator==(Vector2i v) const {
			return x == v.x && y == v.y;
		}
		constexpr bool operator!=(Vector2i v) const {
			return x != v.x || y != v.y;
		}

		inline std::string ToString() {
			return std::format("X: {}, Y: {}", x, y);
		}

		int x;
		int y;

		static constexpr Vector2i Invalid() { return Vector2i(-1, -1); }
	};
}