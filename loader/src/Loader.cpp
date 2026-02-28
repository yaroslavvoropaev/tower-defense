
#include <yaml-cpp/yaml.h>


#include "Loader.h"
//strategy
#include "Weakest.h"
#include "Strongest.h"
#include "AllInRange.h"
#include "NearestToCastle.h"
#include "NearestToTower.h"
//mapper
#include "CastleDTOMapper.h"
#include "CastleMapper.h"
#include "EnemyDTOMapper.h"
#include "EnemyMapper.h"
#include "MagicTowerDTOMapper.h"
#include "MagicTowerMapper.h"
#include "MagicTrapDTOMapper.h"
#include "MagicTrapMapper.h"
#include "SimpleTowerDTOMapper.h"
#include "SimpleTowerMapper.h"
//repository
#include "TowerRepository.h"
#include "EnemyRepository.h"
#include "MapperRepository.h"
#include "StrategyRepository.h"
#include "CastleRepository.h"
//service
#include "EconomyService.h"
#include "ID_service.h"
#include "EnemyService.h"
#include "TowerService.h"
#include "IMoveService.h"
//factory
#include "EffectFactory.h"
#include "TowerFactory.h"
#include "EnemyFactory.h"
#include "CastleFactory.h"
//tower
#include "SimpleTower.h"
#include "MagicTrap.h"
#include "MagicTower.h"
//visitor
#include "SimpleTowerAttackVisitor.h"
#include "MagicTowerAttackVisitor.h"
#include "MagicTrapAttackVisitor.h"
#include "SimpleTowerUpgradeVisitor.h"
#include "MagicTowerUpgradeVisitor.h"
#include "MagicTrapUpgradeVisitor.h"
//presenter
#include "MoveService.h"
#include "Presenter.h"
#include "YamlStateService.h"


TowerDefense::EnemyDTO TowerDefense::Loader::load_enemy_config(const std::string &path) {
    auto config = YAML::LoadFile(path);
    auto enemy_node = config["enemy"];
    auto node = enemy_node[0];
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
    return dto;
}

TowerDefense::CastleDTO TowerDefense::Loader::load_castle_config(const std::string &path) {
    auto config = YAML::LoadFile(path);
    auto castle_nodes = config["castle"];
    auto node = castle_nodes[0];
    auto id = node["id"].as<ID>();
    auto name = node["name"].as<std::string>();
    auto health = node["health"].as<float>();
    auto max_health = node["max_health"].as<float>();
    auto gold = node["gold"].as<size_t>();
    auto x = node["x"].as<size_t>();
    auto y = node["y"].as<size_t>();
    CastleDTO dto{id, std::move(name), health, max_health, gold,  x, y};
    return dto;
}



TowerDefense::EffectConfig TowerDefense::Loader::load_effect_config(const std::string &path) {
    auto config = YAML::LoadFile(path);
    auto enemy_nodes = config["effect"];
    EffectConfig effect_config;
    for (const auto &node : enemy_nodes) {
        auto type = node["type"].as<std::string>();
        auto magnitude = node["magnitude"].as<float>();
        auto duration = node["duration"].as<float>();
        EffectDTO dto{type, magnitude, duration};
        effect_config.effects.push_back(std::move(dto));
    }
    return effect_config;
}

TowerDefense::TowerConfig TowerDefense::Loader::load_tower_config(const std::string &path) {
    TowerConfig config;
    auto yaml_config = YAML::LoadFile(path);
    for (const auto &tower_type_node : yaml_config["tower"]) {
        auto tower_category = tower_type_node.first.as<std::string>();
        std::vector<TowerDTO> all_dto;
        for (const auto &tower_node : tower_type_node.second) {
            auto id = tower_node["id"].as<ID>();
            auto type = tower_node["type"].as<std::string>();
            auto range = tower_node["range"].as<float>();
            auto level = tower_node["level"].as<size_t>();
            auto x = tower_node["x"].as<size_t>();
            auto y = tower_node["y"].as<size_t>();
            auto cost = tower_node["cost"].as<size_t>();
            auto strategy = tower_node["strategy"].as<std::string>();
            auto params = tower_node["params"].as<std::unordered_map<std::string, std::string>>();

            TowerDTO dto {id, std::move(type), range, level, x, y, cost, std::move(strategy), std::move(params)};
            all_dto.push_back(std::move(dto));
        }
        config.towers.emplace(tower_category, all_dto);
    }
    return config;
}

TowerDefense::LevelConfig TowerDefense::Loader::load_level_config(const std::string &path) {
    LevelConfig config;
    auto yaml_config = YAML::LoadFile(path);
    for (const auto &type_node : yaml_config["level"]) {
        auto tower_type = type_node.first.as<std::string>();
        std::vector<LevelDTO> all_level_dto;
        for (const auto &level_node : type_node.second) {
            auto level = level_node["level"].as<size_t>();
            auto cost = level_node["cost"].as<size_t>();
            auto range = level_node["range"].as<float>();
            auto params = level_node["params"].as<std::unordered_map<std::string, float>>();
            LevelDTO dto {level, cost,  range,  std::move(params)};
            all_level_dto.push_back(std::move(dto));
        }
        config.levels.emplace(tower_type, all_level_dto);
    }
    return config;
}


TowerDefense::GameFiled &TowerDefense::Loader::get_game_filed() {
    if (!game_filed_) {
        YAML::Node config = YAML::LoadFile("/home/voropaev/oop2025/3/config/field_config.yaml");
        YAML::Node size_node = config["level"]["size"];
        auto width = size_node[0]["width"].as<size_t>();
        auto height = size_node[1]["height"].as<size_t>();

        game_filed_ = std::make_unique<GameFiled>(width, height);
        Cell cell;
        YAML::Node map_node = config["level"]["map"];
        size_t row = 0;
        size_t col = 0;
        for (const auto &row_node : map_node) {
            col = 0;
            for (const auto &cell_node : row_node) {
                cell.landscape_type = cell_node.as<std::string>();
                game_filed_->set_cell(row, col, cell);
                ++col;
            }
            ++row;
        }
    }
    return *game_filed_;
}

TowerDefense::IEnemyFactory& TowerDefense::Loader::get_enemy_factory() {
    if (!enemy_factory_) {
        enemy_factory_ = std::make_unique<EnemyFactory>(get_id_service(), load_enemy_config("../config/enemy_config.yaml"));
    }
    return *enemy_factory_;
}


TowerDefense::IEffectFactory &TowerDefense::Loader::get_effect_factory() {
    if (!effect_factory_) {
        effect_factory_ = std::make_unique<EffectFactory>(load_effect_config("../config/effect_config.yaml"));
    }
    return *effect_factory_;
}

TowerDefense::ITowerFactory &TowerDefense::Loader::get_tower_factory() {
    if (!tower_factory_) {
        tower_factory_ = std::make_unique<TowerFactory>(get_effect_factory(), get_strategy_repository(), get_castle_repository(), get_id_service(),
            load_tower_config("../config/tower_config.yaml"));
    }
    return *tower_factory_;
}

TowerDefense::IID_service &TowerDefense::Loader::get_id_service() {
    if (!id_service_) {
        id_service_ = std::make_unique<ID_service>();
    }
    return *id_service_;
}

TowerDefense::IEnemyService &TowerDefense::Loader::get_enemy_service() {
    if (!enemy_service_) {
        enemy_service_ = std::make_unique<EnemyService>(get_castle_repository(), get_enemy_repository());
    }
    return *enemy_service_;
}



TowerDefense::IEconomyService &TowerDefense::Loader::get_economy_service() {
    if (!economy_service_) {
        economy_service_ = std::make_unique<EconomyService>(get_tower_repository(), get_castle_repository(), load_level_config("../config/level_config.yaml"));

        economy_service_->add_visitor(typeid(SimpleTower), std::make_unique<SimpleTowerUpgradeVisitor>());
        economy_service_->add_visitor(typeid(MagicTower), std::make_unique<MagicTowerUpgradeVisitor>());
        economy_service_->add_visitor(typeid(MagicTrap), std::make_unique<MagicTrapUpgradeVisitor>());
    }
    return *economy_service_;
}

TowerDefense::ITowerService &TowerDefense::Loader::get_tower_service() {
    if (!tower_service_) {
        tower_service_ = std::make_unique<TowerService>(get_tower_repository(), get_enemy_repository(), get_castle_repository());

        tower_service_->add_visitor(typeid(SimpleTower), std::make_unique<SimpleTowerAttackVisitor>());
        tower_service_->add_visitor(typeid(MagicTower), std::make_unique<MagicTowerAttackVisitor>());
        tower_service_->add_visitor(typeid(MagicTrap), std::make_unique<MagicTrapAttackVisitor>());
    }
    return *tower_service_;
}

TowerDefense::ITowerRepository &TowerDefense::Loader::get_tower_repository()  {
    if (!tower_repository_) {
        tower_repository_ = std::make_unique<TowerRepository>();
    }
    return *tower_repository_;
}

TowerDefense::IEnemyRepository &TowerDefense::Loader::get_enemy_repository()  {
    if (!enemy_repository_) {
        enemy_repository_ = std::make_unique<EnemyRepository>();
    }
    return *enemy_repository_;
}


TowerDefense::IMoveService &TowerDefense::Loader::get_move_service() {
    if (!move_service_) {
        move_service_ = std::make_unique<MoveService>(get_enemy_repository(), get_game_filed());
    }
    return *move_service_;
}

TowerDefense::IPresenter &TowerDefense::Loader::get_presenter() {
    if (!presenter_) {
        presenter_ = std::make_unique<Presenter>(get_game_filed(), get_castle_repository(), get_tower_repository(), get_enemy_repository(), get_mapper_repository(),
        get_enemy_factory(), get_tower_factory(), get_castle_factory(), get_move_service(),
        get_tower_service(), get_enemy_service(), get_economy_service(), get_state_service(), get_id_service());
    }
    return *presenter_;
}

TowerDefense::ICastleRepository &TowerDefense::Loader::get_castle_repository()  {
    if (!castle_repository_) {
        castle_repository_ = std::make_unique<CastleRepository>();
        castle_repository_->add_castle(get_castle_factory().create_castle());
    }
    return *castle_repository_;
}


TowerDefense::ICastleFactory& TowerDefense::Loader::get_castle_factory() {
    if (!castle_factory_) {
        castle_factory_ = std::make_unique<CastleFactory>(get_id_service(), load_castle_config("/home/voropaev/oop2025/3/config/castle_config.yaml"));
    }
    return *castle_factory_;
}

TowerDefense::IStrategyRepository &TowerDefense::Loader::get_strategy_repository() {
    if (!strategy_repository_) {
        strategy_repository_ = std::make_unique<StrategyRepository>();

        strategy_repository_->add_strategy("weakest", std::make_unique<Weakest>(get_enemy_repository()));
        strategy_repository_->add_strategy("strongest", std::make_unique<Strongest>(get_enemy_repository()));
        strategy_repository_->add_strategy("all_in_range", std::make_unique<AllInRange>(get_enemy_repository()));
        strategy_repository_->add_strategy("nearest_to_tower", std::make_unique<NearestToTower>(get_enemy_repository()));
        strategy_repository_->add_strategy("nearest_to_castle", std::make_unique<NearestToCastle>(get_enemy_repository(), get_castle_repository()));
    }
    return *strategy_repository_;
}

TowerDefense::IMapperRepository &TowerDefense::Loader::get_mapper_repository() {
    if (!mapper_repository_) {
        mapper_repository_ = std::make_unique<MapperRepository>();

        mapper_repository_->add_enemy_mapper(std::make_unique<EnemyMapper>());
        mapper_repository_->add_enemy_dto_mapper(std::make_unique<EnemyDTOMapper>());
        mapper_repository_->add_castle_mapper(std::make_unique<CastleMapper>());
        mapper_repository_->add_castle_dto_mapper(std::make_unique<CastleDTOMapper>());
        mapper_repository_->add_tower_mapper("simple_tower", std::make_unique<SimpleTowerMapper>(get_strategy_repository()));
        mapper_repository_->add_tower_mapper("magic_tower", std::make_unique<MagicTowerMapper>(get_strategy_repository(),get_effect_factory()));
        mapper_repository_->add_tower_mapper("magic_trap", std::make_unique<MagicTrapMapper>(get_strategy_repository(), get_effect_factory()));
        mapper_repository_->add_tower_dto_mapper(typeid(SimpleTower), std::make_unique<SimpleTowerDTOMapper>(get_strategy_repository()));
        mapper_repository_->add_tower_dto_mapper( typeid(MagicTower), std::make_unique<MagicTowerDTOMapper>(get_strategy_repository(),get_effect_factory()));
        mapper_repository_->add_tower_dto_mapper(typeid(MagicTrap), std::make_unique<MagicTrapDTOMapper>(get_strategy_repository(), get_effect_factory()));
    }
    return *mapper_repository_;
}

TowerDefense::IStateService &TowerDefense::Loader::get_state_service() {
    if (!state_service_) {
        state_service_ = std::make_unique<YamlStateService>(get_castle_repository(), get_enemy_repository(), get_tower_repository(), get_mapper_repository());
    }
    return *state_service_;
}

