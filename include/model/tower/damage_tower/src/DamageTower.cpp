#include "DamageTower.h"

float TowerDefense::DamageTower::get_damage() const {
    return damage_;
}
void TowerDefense::DamageTower::set_damage(float damage) {
    damage_ = damage;
}

