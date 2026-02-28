#include "CastleMapper.h"
#include "Castle.h"

std::unique_ptr<TowerDefense::ICastle> TowerDefense::CastleMapper::transform(const CastleDTO &dto) {
    return std::make_unique<Castle>(dto.id, dto.name, dto.health, dto.max_health, dto.gold, Point(dto.x, dto.y));
}
