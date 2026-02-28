
#include "EffectModule.h"


void TowerDefense::EffectModule::add_effect(IEnemy &enemy, std::unique_ptr<IEffect> effect) {
    effect->apply_effect(enemy);
    std::lock_guard lock(mutex_);
    effects_.push_back(std::move(effect));
}

void TowerDefense::EffectModule::all_update(IEnemy &enemy, float dt) {
    for (auto it = effects_.begin(); it != effects_.end();) {
        (*it)->update_effect(enemy, dt);
        if ((*it)->is_finished()) {
            it = effects_.erase(it);
        } else {
            ++it;
        }
    }
}