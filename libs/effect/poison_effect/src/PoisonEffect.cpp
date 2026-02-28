
#include "PoisonEffect.h"
#include "IEnemy.h"

void TowerDefense::PoisonEffect::apply_effect([[maybe_unused]] IEnemy &enemy) {}

std::unique_ptr<TowerDefense::IEffect> TowerDefense::PoisonEffect::clone() {
    return std::make_unique<PoisonEffect>(magnitude_, duration_);
}


void TowerDefense::PoisonEffect::update_effect(IEnemy &enemy, float dt) {
    duration_ -= dt;
    if (duration_ <= 0) {
        is_finished_ = true;
        return;
    }
    enemy.take_damage(magnitude_);
}


bool TowerDefense::PoisonEffect::is_finished() {
    return is_finished_;
}


