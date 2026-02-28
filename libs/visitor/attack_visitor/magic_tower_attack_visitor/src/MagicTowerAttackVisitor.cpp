#include "MagicTowerAttackVisitor.h"
#include "MagicTower.h"


TowerDefense::AttackInfo TowerDefense::MagicTowerAttackVisitor::visit(ITower& tower, float dt) {
    AttackInfo res{};
    auto &magic_tower = dynamic_cast<MagicTower &>(tower);
    if (!magic_tower.try_attack(dt)) {
        return res;;
    }
    std::vector<IEnemy *> enemies = magic_tower.find_target();
    if (enemies.empty()) {
        return res;
    }
    res.range = magic_tower.get_range();
    res.tower_id = magic_tower.get_id();
    res.tower_type = "magic_tower";
    res.tower_x = magic_tower.get_position().x_;
    res.tower_y = magic_tower.get_position().y_;
    for (auto enemy : enemies) {
        res.enemy_id = enemy->get_ID();
        res.enemy_x_pixels = enemy->get_x_pixels();
        res.enemy_y_pixels = enemy->get_y_pixels();
        enemy->add_effect(magic_tower.get_effect());
        enemy->take_damage(magic_tower.get_damage());
    }
    return res;
}