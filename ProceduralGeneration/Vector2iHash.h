#pragma once

#include <SFML/System/Vector2.hpp>
#include <functional>

namespace std {
    template <>
    struct hash<sf::Vector2i> {
        size_t operator()(const sf::Vector2i& v) const {
            return std::hash<int>()(v.x) ^ (std::hash<int>()(v.y) << 1);
        }
    };

    inline bool operator==(const sf::Vector2i& lhs, const sf::Vector2i& rhs) {
        return lhs.x == rhs.x && lhs.y == rhs.y;
    }
}
