#include "MagicTrap.h"

std::unique_ptr<TowerDefense::ITower> TowerDefense::MagicTrap::clone()  {
    return std::make_unique<MagicTrap>(get_id(), get_range(), get_level(), get_position(), get_strategy(), get_rate_of_fire(), get_effect());
}