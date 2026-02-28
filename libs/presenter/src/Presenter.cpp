#include "Presenter.h"


TowerDefense::MapDto TowerDefense::Presenter::get_map() const {
    MapDto map;
    map.height = game_filed_.get_height();
    map.width = game_filed_.get_width();
    for (size_t i = 0; i < game_filed_.get_height(); i++) {
        std::vector<std::string> row;
        for (size_t j = 0; j < game_filed_.get_width(); j++) {
            row.push_back(game_filed_.get_cell(i, j).landscape_type);
        }
        map.landscape_type.push_back(row);
    }
    return map;
}

std::vector<TowerDefense::EnemyDTO> TowerDefense::Presenter::get_enemies() const {
    std::vector<EnemyDTO> res;
    auto enemies = enemy_repository_.get_all();
    for (auto enemy : enemies) {
        res.push_back(mapper_repository_.enemy_to_dto(enemy));
    }
    return res;
}


std::vector<TowerDefense::TowerDTO> TowerDefense::Presenter::get_towers() const {
    std::vector<TowerDTO> res;
    auto towers = tower_repository_.get_all();
    for (auto tower : towers) {
        res.push_back(mapper_repository_.tower_to_dto(tower));
    }
    return res;
}


void TowerDefense::Presenter::add_enemy() {
    auto enemy = enemy_factory_.create_enemy();
    enemy_repository_.add_enemy(std::move(enemy));
}

void TowerDefense::Presenter::move(float dt) {
    move_service_.move(dt);
}

void TowerDefense::Presenter::add_tower(const std::string &type, size_t x, size_t y) {
    auto tower = tower_factory_.create_tower(type, Point(x, y));
    if (tower != nullptr) {
        tower_repository_.add_tower(std::move(tower));
    }
}

std::vector<TowerDefense::AttackInfo> TowerDefense::Presenter::tower_attack(float dt){
    std::vector<AttackInfo> info = tower_service_.attack_all(dt);
    return info;
}

TowerDefense::CastleDTO TowerDefense::Presenter::get_castle() const {
    auto castle = castle_repository_.get();
    CastleDTO res = mapper_repository_.castle_to_dto(castle);
    return res;
}

void TowerDefense::Presenter::enemy_attack() {
    enemy_service_.attack_all();
}

void TowerDefense::Presenter::upgrade_tower(ID id) {
    economy_service_.upgrade(id);
}

void TowerDefense::Presenter::save() const {
    state_service_.save_castle("../save_load/castle.yaml");
    state_service_.save_enemy("../save_load/enemy.yaml");
    state_service_.save_tower("../save_load/tower.yaml");
}


void TowerDefense::Presenter::load() const {
    state_service_.load_castle("../save_load/castle.yaml");
    state_service_.load_enemy("../save_load/enemy.yaml");
    state_service_.load_tower("../save_load/tower.yaml");
    size_t max_id = 1;
    for (auto &tower : tower_repository_.get_all()) {
        if (max_id < tower->get_id()) {
            max_id = tower->get_id();
        }
    }
    for (auto &enemy : enemy_repository_.get_all()) {
        if (max_id < enemy->get_ID()) {
            max_id = enemy->get_ID();
        }
    }
    if (max_id < castle_repository_.get()->get_ID()) {
        max_id = castle_repository_.get()->get_ID();
    }
    id_service_.set_id(max_id);
}

void TowerDefense::Presenter::reset() {
    tower_repository_.reset();
    enemy_repository_.reset();
    castle_repository_.add_castle(castle_factory_.create_castle());
}
