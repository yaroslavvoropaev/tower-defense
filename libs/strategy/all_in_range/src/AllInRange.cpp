#include "IEnemy.h"
#include "AllInRange.h"



std::vector<TowerDefense::IEnemy *> TowerDefense::AllInRange::find_target(float range, TowerDefense::Point position) {
    return enemy_repository_.get_in_range(position, range);
}
