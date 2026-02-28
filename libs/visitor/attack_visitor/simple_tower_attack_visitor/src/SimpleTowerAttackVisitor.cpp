#include "SimpleTowerAttackVisitor.h"

#include <iostream>

#include "SimpleTower.h"

TowerDefense::AttackInfo TowerDefense::SimpleTowerAttackVisitor::visit(ITower &tower, float dt) {
    AttackInfo res{};
    auto &simple_tower = dynamic_cast<SimpleTower &>(tower);
    if (!simple_tower.try_attack(dt)) {
        return res;
    }
    std::vector<IEnemy *> enemies = simple_tower.find_target();
    if (enemies.empty()) {
        return res;
    }
    res.range = simple_tower.get_range();
    res.tower_id = simple_tower.get_id();
    res.tower_type = "simple_tower";
    res.tower_x = simple_tower.get_position().x_;
    res.tower_y = simple_tower.get_position().y_;
    for (auto enemy : enemies) {
        res.enemy_id = enemy->get_ID();
        res.enemy_x_pixels = enemy->get_x_pixels();
        res.enemy_y_pixels = enemy->get_y_pixels();
        enemy->take_damage(simple_tower.get_damage());
    }
    return res;
}
