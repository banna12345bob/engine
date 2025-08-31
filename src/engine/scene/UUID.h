#pragma once

#include <cmath>
#include <unordered_set>
#include <set>

namespace Engine {

	class UUID {
	public:
		UUID(int id)
		{
			ID = id;
		}

		static UUID GenerateUUID() {
			s_NextUUID++;
			return UUID(s_NextUUID);
		}

		operator int() const { return ID; }

		int ID;
	private:
		inline static int s_NextUUID;
	};

}


template<> struct std::hash<Engine::UUID> {
	std::size_t operator()(Engine::UUID const& s) const noexcept {
		std::size_t h1 = std::hash<int>{}(s);
		return h1;
	}
};