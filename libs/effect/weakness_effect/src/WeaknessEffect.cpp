#include "WeaknessEffect.h"
#include "IEnemy.h"

void TowerDefense::WeaknessEffect::apply_effect(IEnemy &enemy) {
    enemy.change_weakness(magnitude_);
}
void TowerDefense::WeaknessEffect::update_effect(IEnemy &enemy, float dt) {
    duration_ -= dt;
    if (duration_ <= 0) {
        is_finished_ = true;
        enemy.change_weakness(-magnitude_);
    }
}

std::unique_ptr<TowerDefense::IEffect> TowerDefense::WeaknessEffect::clone() {
    return std::make_unique<WeaknessEffect>(magnitude_, duration_);
}

bool TowerDefense::WeaknessEffect::is_finished() {
    return is_finished_;
}



