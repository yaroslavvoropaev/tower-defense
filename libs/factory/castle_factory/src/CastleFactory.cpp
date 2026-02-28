#include "CastleFactory.h"


std::unique_ptr<TowerDefense::ICastle> TowerDefense::CastleFactory::create_castle() const {
    return std::make_unique<Castle>(id_service_.get_id(), castle_dto_.name, castle_dto_.health, castle_dto_.max_health, castle_dto_.gold, Point(castle_dto_.x, castle_dto_.y));
}

