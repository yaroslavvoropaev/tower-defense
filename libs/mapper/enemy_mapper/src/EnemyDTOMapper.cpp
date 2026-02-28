#include "EnemyDTOMapper.h"

TowerDefense::EnemyDTO TowerDefense::EnemyDTOMapper::transform(const IEnemy *enemy) {
    EnemyDTO dto {enemy->get_ID(), enemy->get_name(),  enemy->get_health(), enemy->get_max_health(), enemy->get_gold(), enemy->get_speed(),
                    enemy->get_position().x_, enemy->get_position().y_,
             enemy->get_x_pixels(), enemy->get_y_pixels()};
    return dto;
}









