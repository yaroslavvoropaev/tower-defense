#include "YamlStateService.h"
#include <fstream>
#include <yaml-cpp/yaml.h>



void TowerDefense::YamlStateService::load_enemy(const std::string &path) {
    auto config = YAML::LoadFile(path);
    auto enemy_nodes = config["enemy"];

    for (const auto &node : enemy_nodes) {
        auto id = node["id"].as<ID>();
        auto name = node["name"].as<std::string>();
        auto health = node["health"].as<float>();
        auto max_health = node["max_health"].as<float>();
        auto gold = node["gold"].as<size_t>();
        auto speed = node["speed"].as<float>();
        auto x = node["x"].as<size_t>();
        auto y = node["y"].as<size_t>();
        auto x_pixels = node["x_pixels"].as<float>();
        auto y_pixels = node["y_pixels"].as<float>();
        EnemyDTO dto{id, std::move(name), health, max_health, gold, speed, x, y, x_pixels, y_pixels};
        auto enemy = mapper_repository_.dto_to_enemy(dto);
        enemy_repository_.add_enemy(std::move(enemy));
    }
}

void TowerDefense::YamlStateService::load_castle(const std::string &path) {
    auto config = YAML::LoadFile(path);
    auto castle_nodes = config["castle"];

    for (const auto &node : castle_nodes) {
        auto id = node["id"].as<ID>();
        auto name = node["name"].as<std::string>();
        auto health = node["health"].as<float>();
        auto max_health = node["max_health"].as<float>();
        auto gold = node["gold"].as<size_t>();
        auto x = node["x"].as<size_t>();
        auto y = node["y"].as<size_t>();
        CastleDTO dto{id, std::move(name), health, max_health, gold, x, y};
        auto castle = mapper_repository_.dto_to_castle(dto);
        castle_repository_.add_castle(std::move(castle));
    }
}

void TowerDefense::YamlStateService::load_tower(const std::string &path) {
    auto config = YAML::LoadFile(path);
    auto tower_nodes = config["tower"];

    for (const auto &node : tower_nodes) {
        auto id = node["id"].as<ID>();
        auto type = node["type"].as<std::string>();
        auto range = node["range"].as<float>();
        auto level = node["level"].as<size_t>();
        auto x = node["x"].as<size_t>();
        auto y = node["y"].as<size_t>();
        auto strategy = node["strategy"].as<std::string>();
        auto params = node["params"].as<std::unordered_map<std::string, std::string>>();
        TowerDTO dto{id, std::move(type), range, level,  x, y, 0, std::move(strategy), std::move(params)};
        auto tower = mapper_repository_.dto_to_tower(dto);
        tower_repository_.add_tower(std::move(tower));
    }
}


void TowerDefense::YamlStateService::save_enemy(const std::string &path) {
    std::ofstream out(path);
    YAML::Emitter emitter(out);
    emitter << YAML::BeginMap
            << YAML::Key << "enemy"
            << YAML::Value << YAML::BeginSeq;

    std::vector<IEnemy *>enemies = enemy_repository_.get_all();
    for (const auto &enemy : enemies) {
        EnemyDTO dto = mapper_repository_.enemy_to_dto(enemy);
        emitter << YAML::BeginMap
                << YAML::Key << "name"
                << YAML::Value << dto.name
                << YAML::Key << "id"
                << YAML::Value << dto.id
                << YAML::Key << "speed"
                << YAML::Value << std::to_string(dto.speed)
                << YAML::Key << "health"
                << YAML::Value << std::to_string(dto.health)
                << YAML::Key << "max_health"
                << YAML::Value << std::to_string(dto.max_health)
                << YAML::Key << "gold"
                << YAML::Value << dto.gold
                << YAML::Key << "x"
                << YAML::Value  << std::to_string(dto.x)
                << YAML::Key << "y"
                << YAML::Value  << std::to_string(dto.y)
                << YAML::Key << "x_pixels"
                << YAML::Value << std::to_string(dto.x_pixels)
                << YAML::Key << "y_pixels"
                << YAML::Value << std::to_string(dto.y_pixels)
                << YAML::EndMap;
    }
    emitter << YAML::EndSeq << YAML::EndMap;
}


void TowerDefense::YamlStateService::save_castle(const std::string &path) {
    std::ofstream out(path);
    YAML::Emitter emitter(out);
    emitter << YAML::BeginMap
            << YAML::Key << "castle"
            << YAML::Value << YAML::BeginSeq;

    ICastle *castle = castle_repository_.get();

    CastleDTO dto = mapper_repository_.castle_to_dto(castle);
    emitter << YAML::BeginMap
            << YAML::Key << "name"
            << YAML::Value << dto.name
            << YAML::Key << "id"
            << YAML::Value << dto.id
            << YAML::Key << "health"
            << YAML::Value << std::to_string(dto.health)
            << YAML::Key << "max_health"
            << YAML::Value << std::to_string(dto.max_health)
            << YAML::Key << "gold"
            << YAML::Value << dto.gold
            << YAML::Key << "x"
            << YAML::Value << std::to_string(dto.x)
            << YAML::Key << "y"
            << YAML::Value  << std::to_string(dto.y)
            << YAML::EndMap;
    emitter << YAML::EndSeq << YAML::EndMap;
}

void TowerDefense::YamlStateService::save_tower(const std::string &path) {
    std::ofstream out(path);
    YAML::Emitter emitter(out);
    emitter << YAML::BeginMap
            << YAML::Key << "tower"
            << YAML::Value << YAML::BeginSeq;

    std::vector<ITower *> towers = tower_repository_.get_all();
    for (const auto &tower : towers) {
        TowerDTO dto = mapper_repository_.tower_to_dto(tower);
        emitter << YAML::BeginMap
                << YAML::Key << "id"
                << YAML::Value << dto.id
                << YAML::Key << "type"
                << YAML::Value << dto.type
                << YAML::Key << "range"
                << YAML::Value << std::to_string(dto.range)
                << YAML::Key << "level"
                << YAML::Value << dto.level
                << YAML::Key << "x"
                << YAML::Value  << std::to_string(dto.x)
                << YAML::Key << "y"
                << YAML::Value  << std::to_string(dto.y)
                << YAML::Key << "strategy"
                << YAML::Value << dto.strategy
                << YAML::Key << "params"
                << YAML::BeginMap;
        for (const auto& [key, value] : dto.properties) {
            emitter << YAML::Key << key
                    << YAML::Value << value;
        }
        emitter << YAML::EndMap
                << YAML::EndMap;
    }
    emitter << YAML::EndSeq << YAML::EndMap;
}


