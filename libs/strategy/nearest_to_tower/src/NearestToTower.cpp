#include "NearestToTower.h"
#include <cmath>


std::vector<TowerDefense::IEnemy *> TowerDefense::NearestToTower::find_target(float range, Point position) {
    IEnemy *enemy = enemy_repository_.find_target(
        [&position](auto &lhs, auto &rhs) {
            return sqrt(pow(static_cast<int>(lhs->get_position().x_) - static_cast<int>(position.y_), 2) + pow(static_cast<int>(lhs->get_position().y_) - static_cast<int>(position.x_), 2)) <
                   sqrt(pow(static_cast<int>(rhs->get_position().x_) - static_cast<int>(position.y_), 2) + pow(static_cast<int>(rhs->get_position().y_) - static_cast<int>(position.x_), 2));
        },[&](auto &val) {
            return sqrt(pow(static_cast<int>(val->get_position().y_) - static_cast<int>(position.x_), 2) +
                          pow(static_cast<int>(val->get_position().x_) - static_cast<int>(position.y_), 2)) < range;
    });
    std::vector<IEnemy *> res;
    if (enemy != nullptr) {
        res.push_back(enemy);
    }
    return res;
}

