#include "MagicTowerMapper.h"
#include "MagicTower.h"


std::unique_ptr<TowerDefense::ITower> TowerDefense::MagicTowerMapper::transform(const TowerDTO &dto)  {
    return std::make_unique<MagicTower>(dto.id, dto.range, dto.level, Point(dto.x, dto.y), strategy_repository_.get_strategy(dto.strategy),
        std::stof(dto.properties.at("damage")), std::stof(dto.properties.at("rate_of_fire")),
        effect_factory_.create_effect(dto.properties.at("effect")));
}

