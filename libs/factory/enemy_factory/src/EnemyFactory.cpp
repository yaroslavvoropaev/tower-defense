#include "EnemyFactory.h"


std::unique_ptr<TowerDefense::IEnemy> TowerDefense::EnemyFactory::create_enemy() const {
    auto tmp = enemy->clone();
    tmp->set_ID(id_service_.get_id());
    return tmp;
}

