#include "SimpleTowerUpgradeVisitor.h"
#include "SimpleTower.h"

void TowerDefense::SimpleTowerUpgradeVisitor::visit(ITower &tower, LevelDTO &dto) {
    auto &simple_tower = dynamic_cast<SimpleTower &>(tower);
    simple_tower.set_range(dto.range);
    simple_tower.set_damage(dto.properties.at("damage"));
    simple_tower.set_rate_of_fire(dto.properties.at("rate_of_fire"));
}



