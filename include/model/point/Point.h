#pragma once

#include <functional>
#include <cstddef>

namespace TowerDefense {
    struct Point {
        size_t x_;
        size_t y_;
        explicit Point(size_t x = 0, size_t y = 0) {
            x_ = x;
            y_ = y;
        }
        Point operator+(const Point &other) const;
        Point operator-(const Point &other) const;
        [[nodiscard]] float length(const Point &) const;
        bool operator==(const Point &other) const {
            if (x_ == other.x_ && y_ == other.y_) return true;
            return false;
        }

    };
    struct PointHash {
        std::size_t operator()(const Point &p) const {
            return std::hash<size_t>()(p.x_) ^ (std::hash<size_t>()(p.y_) << 1);
        }
    };
}
