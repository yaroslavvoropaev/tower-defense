#pragma once

#include <chrono>
#include <string>
#include <unordered_map>
#include "id.h"

namespace TowerDefense {

    struct MapDto {
        size_t width;
        size_t height;
        std::vector<std::vector<std::string>> landscape_type;
    };

    struct AttackInfo {
        float range;
        ID tower_id;
        std::string tower_type;
        size_t tower_x;
        size_t tower_y;
        ID enemy_id;
        float enemy_x_pixels;
        float enemy_y_pixels;
        bool operator==(const AttackInfo&) const = default;
    };

    struct TowerDTO {
        ID id;
        std::string type;
        float range;
        size_t level;
        size_t x;
        size_t y;
        size_t cost;
        std::string strategy;
        std::unordered_map<std::string, std::string> properties;
        bool operator==(const TowerDTO&) const = default;
    };

    struct EnemyDTO {
        ID id;
        std::string name;
        float health;
        float max_health;
        size_t gold;
        float speed;
        size_t x;
        size_t y;
        float x_pixels;
        float y_pixels;
        bool operator==(const EnemyDTO&) const = default;
    };


    struct CastleDTO {
        ID id;
        std::string name;
        float health;
        float max_health;
        size_t gold;
        size_t x;
        size_t y;
        bool operator==(const CastleDTO&) const = default;
    };

    struct EffectDTO {
        std::string type;
        float magnitude;
        float duration;
    };

    struct EffectConfig {
        std::vector<EffectDTO> effects;
    };

    struct LevelDTO {
        size_t level;
        size_t cost;
        float range;
        std::unordered_map<std::string, float> properties;
    };

    struct LevelConfig {
        std::unordered_map<std::string, std::vector<LevelDTO>> levels;
    };

    struct TowerConfig {
        std::unordered_map<std::string, std::vector<TowerDTO>> towers;
    };

}
