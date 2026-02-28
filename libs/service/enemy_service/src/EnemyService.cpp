#include "EnemyService.h"

#include <iostream>


void TowerDefense::EnemyService::attack_all() {
    auto castle = castle_repository_.get();
    std::vector<IEnemy *> enemies = enemy_repository_.get_all();
    for (auto enemy : enemies) {
        if (enemy->get_position().x_ == castle->get_position().x_ && enemy->get_position().y_ == castle->get_position().y_) {
            castle->take_damage(enemy->get_health());
            if (castle->get_health() <= 0) {
                castle->set_health(0);
            }
            enemy_repository_.delete_enemy(enemy->get_ID());
        }
    }
}

