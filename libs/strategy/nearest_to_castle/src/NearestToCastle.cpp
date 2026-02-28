#include "NearestToCastle.h"

#include <cmath>
#include <iostream>


std::vector<TowerDefense::IEnemy *> TowerDefense::NearestToCastle::find_target(float range, Point position) {
    ICastle *castle = castle_repository_.get();
    Point castle_position = castle->get_position();
    IEnemy *enemy = enemy_repository_.find_target(
        [&castle_position] (auto &lhs, auto &rhs) {
            return sqrt(pow(static_cast<int>(lhs->get_position().x_) - static_cast<int>(castle_position.x_), 2) + pow(static_cast<int>(lhs->get_position().y_) - static_cast<int>(castle_position.y_), 2)) <
                   sqrt(pow(static_cast<int>(rhs->get_position().x_) - static_cast<int>(castle_position.x_), 2) + pow(static_cast<int>(rhs->get_position().y_) - static_cast<int>(castle_position.y_), 2));
        },[&](auto &val) {
            return sqrt(pow(static_cast<int>(val->get_position().x_) - static_cast<int>(position.y_), 2) +
                          pow(static_cast<int>(val->get_position().y_) - static_cast<int>(position.x_), 2)) < range;
    });
    std::vector<IEnemy *> res;
    if (enemy != nullptr) {
        res.push_back(enemy);
    }
    return res;
}