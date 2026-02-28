#include "MagicTower.h"

std::unique_ptr<TowerDefense::ITower> TowerDefense::MagicTower::clone() {
    return  std::make_unique<MagicTower>(get_id(), get_range(), get_level(), get_position(), get_strategy(), get_damage(), get_rate_of_fire(), get_effect());
}