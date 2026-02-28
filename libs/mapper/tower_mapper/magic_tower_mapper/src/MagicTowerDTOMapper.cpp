#include "MagicTowerDTOMapper.h"
#include "MagicTower.h"



TowerDefense::TowerDTO TowerDefense::MagicTowerDTOMapper::transform(const ITower *tower) {
    TowerDTO dto {tower->get_id(), "magic_tower",  tower->get_range(), tower->get_level(), tower->get_position().x_, tower->get_position().y_,
        0, strategy_repository_.get_strategy_name(tower->get_strategy()),
        {{"damage", std::to_string(dynamic_cast<const IDamageable *>(tower)->get_damage())},
        {"rate_of_fire", std::to_string(tower->get_rate_of_fire())},
        {"effect", effect_factory_.get_effect_name(dynamic_cast<const IEffectHaveable *>(tower)->get_effect().get())}}};
    return dto;
}


