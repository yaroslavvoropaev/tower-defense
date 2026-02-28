#include "SimpleTower.h"




std::unique_ptr<TowerDefense::ITower> TowerDefense::SimpleTower::clone() {
    return std::make_unique<SimpleTower>(get_id(), get_range(), get_level(), get_position(), get_strategy(), get_damage(), get_rate_of_fire());
}