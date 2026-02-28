#include "EffectFactory.h"


std::unique_ptr<TowerDefense::IEffect> TowerDefense::EffectFactory::create_effect(const std::string &type) const {
    return effects_.at(type)->clone();
}

std::string TowerDefense::EffectFactory::get_effect_name(IEffect *effect) const {
    return effect_types_.at(typeid(*effect));

}
