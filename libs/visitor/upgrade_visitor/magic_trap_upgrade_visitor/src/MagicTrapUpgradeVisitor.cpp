#include "MagicTrapUpgradeVisitor.h"
#include "MagicTrap.h"

void TowerDefense::MagicTrapUpgradeVisitor::visit(ITower &tower, LevelDTO &dto) {
    auto &magic_trap = dynamic_cast<MagicTrap &>(tower);
    magic_trap.set_range(dto.range);
    magic_trap.set_rate_of_fire(dto.properties.at("rate_of_fire"));
}


