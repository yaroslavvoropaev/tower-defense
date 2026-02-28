#include "EffectTower.h"


std::unique_ptr<TowerDefense::IEffect> TowerDefense::EffectTower::get_effect() const {
    return effect_->clone();
}