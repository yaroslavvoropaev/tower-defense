#include "MagicTrapAttackVisitor.h"
#include "MagicTrap.h"

TowerDefense::AttackInfo TowerDefense::MagicTrapAttackVisitor::visit(ITower& tower, float dt) {
    AttackInfo res{};
    auto &magic_trap = dynamic_cast<MagicTrap &>(tower);
    if (!magic_trap.try_attack(dt)) {
        return res;
    }
    std::vector<IEnemy *> enemies = magic_trap.find_target();
    if (enemies.empty()) {
        return res;
    }
    res.range = magic_trap.get_range();
    res.tower_id = magic_trap.get_id();
    res.tower_type = "magic_trap";
    res.tower_x = magic_trap.get_position().x_;
    res.tower_y = magic_trap.get_position().y_;
    for (auto enemy : enemies) {
        enemy->add_effect(magic_trap.get_effect());
    }
    return res;
}