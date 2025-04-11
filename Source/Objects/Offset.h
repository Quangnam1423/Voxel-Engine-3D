#pragma once
#include <functional>

struct Offset {
	int x;
	int y;
	bool operator==(const Offset& other) const {
		return x == other.x && y == other.y;
	}

	bool operator!=(const Offset& other) const {
		return !(*this == other);
	}
};

namespace std {
	template <>
	struct hash<Offset> {
		size_t operator()(const Offset& offset) const {
			return hash<int>()(offset.x) ^ (hash<int>()(offset.y) << 1);
		}
	};
}