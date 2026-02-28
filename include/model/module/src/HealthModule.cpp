
#include "HealthModule.h"

#include <algorithm>


float TowerDefense::HealthModule::get_current_health() const {
    return health_;
}

void TowerDefense::HealthModule::take_damage(float damage) {
    float current_health = health_.load();
    float next_health;
    do {
        next_health = current_health - std::min(current_health, damage * (1.0f + static_cast<float>(weaknessC_) * 0.01f));
    } while (!health_.compare_exchange_weak(current_health, next_health));
    //health_ -= damage * (1.0f + static_cast<float>(weaknessC_) * 0.01f);
}

void TowerDefense::HealthModule::change_weakness(int weakness) {
    weaknessC_ += weakness;
}

float TowerDefense::HealthModule::get_max_health() const {
    return max_health_;
}