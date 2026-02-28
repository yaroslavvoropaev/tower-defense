#include "AbstractTower.h"

#include "IAttackVisitor.h"
#include "IUpgradeVisitor.h"


float TowerDefense::AbstractTower::get_range() const {
    return range_;
}

void TowerDefense::AbstractTower::set_range(float range) {
    range_ = range;
}

size_t TowerDefense::AbstractTower::get_level() const {
    return level_;
}

void TowerDefense::AbstractTower::set_level(size_t level) {
    level_ = level;
}

TowerDefense::AttackInfo TowerDefense::AbstractTower::accept_attack_visitor(IAttackVisitor &attack_visitor, float dt) {
    return attack_visitor.visit(*this, dt);
}

void TowerDefense::AbstractTower::accept_upgrade_visitor(IUpgradeVisitor &upgrade_visitor, LevelDTO &level_dto) {
    upgrade_visitor.visit(*this, level_dto);
}

TowerDefense::Point TowerDefense::AbstractTower::get_position() const {
    return location_;
}

void TowerDefense::AbstractTower::set_position(const Point& location) {
    location_ = location;
}


TowerDefense::ID TowerDefense::AbstractTower::get_id() const {
    return id_;
}


float TowerDefense::AbstractTower::get_rate_of_fire() const {
    return rate_of_fire_;
}
void TowerDefense::AbstractTower::set_rate_of_fire(float rate) {
    rate_of_fire_ = rate;
}

bool TowerDefense::AbstractTower::try_attack(float dt) {
    cooldown_ -= dt;
    if(cooldown_ <= 0) {
        cooldown_ = 1/rate_of_fire_;
        return true;
    }
    return false;
}

void TowerDefense::AbstractTower::set_ID(ID id) {
    id_ = id;
}

TowerDefense::IStrategy *TowerDefense::AbstractTower::get_strategy() const {
    return strategy_;
}

std::vector<TowerDefense::IEnemy *> TowerDefense::AbstractTower::find_target() {
    std::vector<IEnemy *> enemies = strategy_->find_target(range_, location_);
    return enemies;
}
