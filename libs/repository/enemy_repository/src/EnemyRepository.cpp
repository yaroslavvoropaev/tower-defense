#include "EnemyRepository.h"

#include <ranges>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <execution>

void TowerDefense::EnemyRepository::add_enemy(std::unique_ptr<IEnemy> enemy) {
    enemies_.emplace(enemy->get_ID(), std::move(enemy));
}

void TowerDefense::EnemyRepository::delete_enemy(ID id) {
    enemies_.erase(id);
}

TowerDefense::IEnemy* TowerDefense::EnemyRepository::get(ID id) {
    return enemies_.at(id).get();
}

std::vector<TowerDefense::IEnemy*> TowerDefense::EnemyRepository::get_all() {
    std::vector<IEnemy*> res;
    res.reserve(enemies_.size());
    for (const auto& enemy : enemies_ | std::views::values) {
        res.push_back(enemy.get());
    }
    return res;
}

TowerDefense::IEnemy *TowerDefense::EnemyRepository::find_target(
    const std::function<bool(const std::unique_ptr<IEnemy> &, const std::unique_ptr<IEnemy> &)> comp,
    const std::function<bool(const std::unique_ptr<IEnemy> &)> filter) const {
    auto view = enemies_ | std::ranges::views::values | std::ranges::views::filter(filter);
    const auto target = std::ranges::min_element(view, comp);
    if (target == view.end()) return {};
    return (*target).get();
}


std::vector<TowerDefense::IEnemy*> TowerDefense::EnemyRepository::get_in_range(Point position, float range) {
    std::vector<IEnemy*> res;
    for (const auto &enemy : enemies_ | std::views::values) {
        if (pow(static_cast<int>(enemy->get_position().y_) - static_cast<int>(position.x_), 2) +
            pow(static_cast<int>(enemy->get_position().x_) - static_cast<int>(position.y_), 2) < range * range) {
            res.push_back(enemy.get());
            }
    }
    return res;
}


void TowerDefense::EnemyRepository::reset() {
    enemies_.clear();
}