#include "MagicTrapDTOMapper.h"
#include "MagicTrap.h"


TowerDefense::TowerDTO TowerDefense::MagicTrapDTOMapper::transform(const ITower *tower) {
    TowerDTO dto {tower->get_id(), "magic_trap", tower->get_range(), tower->get_level(), tower->get_position().x_, tower->get_position().y_,
        0, strategy_repository_.get_strategy_name(tower->get_strategy()),
        {{"effect", effect_factory_.get_effect_name(dynamic_cast<const IEffectHaveable *>(tower)->get_effect().get())}, {"rate_of_fire", std::to_string(tower->get_rate_of_fire())} }};
    return dto;
}



