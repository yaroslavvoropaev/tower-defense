#include "SimpleTowerMapper.h"
#include "SimpleTower.h"

std::unique_ptr<TowerDefense::ITower> TowerDefense::SimpleTowerMapper::transform(const TowerDTO &dto)  {
    return std::make_unique<SimpleTower>(dto.id, dto.range, dto.level, Point(dto.x, dto.y), strategy_repository_.get_strategy(dto.strategy),
        std::stof(dto.properties.at("damage")), std::stof(dto.properties.at("rate_of_fire")));
}
