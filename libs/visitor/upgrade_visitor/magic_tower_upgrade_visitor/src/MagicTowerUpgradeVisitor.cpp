#include "MagicTowerUpgradeVisitor.h"
#include "MagicTower.h"

void TowerDefense::MagicTowerUpgradeVisitor::visit(ITower &tower, LevelDTO &dto) {
    auto &magic_tower = dynamic_cast<MagicTower &>(tower);
    magic_tower.set_range(dto.range);
    magic_tower.set_damage(dto.properties.at("damage"));
    magic_tower.set_rate_of_fire(dto.properties.at("rate_of_fire"));
}


