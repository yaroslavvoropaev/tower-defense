#include "TowerFactory.h"

std::unique_ptr<TowerDefense::ITower> TowerDefense::TowerFactory::create_tower(const std::string &type, const Point &pos) const {
    if (castle_repository_.get()->get_gold() < costs_.at(type)) {
        return nullptr;
    }
    castle_repository_.get()->subtract_gold(costs_.at(type));
    auto tmp_tower =  towers_.at(type)->clone();
    tmp_tower->set_ID(id_service_.get_id());
    tmp_tower->set_position(pos);
    return tmp_tower;
}

