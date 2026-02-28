#include "EnemyMapper.h"
#include "Enemy.h"

std::unique_ptr<TowerDefense::IEnemy> TowerDefense::EnemyMapper::transform(const EnemyDTO &dto) {
    return std::make_unique<Enemy>(dto.id, dto.name, dto.gold, dto.health, dto.max_health, dto.speed,
        Point(dto.x, dto.y), dto.x_pixels, dto.y_pixels);
}

