
#include "SlowEffect.h"
#include "IEnemy.h"


void TowerDefense::SlowEffect::apply_effect(IEnemy &enemy) {
    enemy.change_deceleration(magnitude_);
}

std::unique_ptr<TowerDefense::IEffect> TowerDefense::SlowEffect::clone() {
    return std::make_unique<SlowEffect>(magnitude_, duration_);
}

void TowerDefense::SlowEffect::update_effect(IEnemy &enemy, float dt) {
    duration_ -= dt;
    if (duration_ <= 0) {
        is_finished_ = true;
        enemy.change_deceleration(-magnitude_);
    }
}

bool TowerDefense::SlowEffect::is_finished() {
    return is_finished_;
}


