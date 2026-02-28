#include "TowerRepository.h"

#include <ranges>

void TowerDefense::TowerRepository::add_tower(std::unique_ptr<ITower> tower) {
    towers_.insert(std::make_pair(tower->get_id(), std::move(tower)));
}


std::vector<TowerDefense::ITower*> TowerDefense::TowerRepository::get_all() {
    std::vector<ITower *> res;
    res.reserve(towers_.size());
    for (const auto &tower : towers_ | std::views::values) {
        res.push_back(tower.get());
    }
    return res;
}

void TowerDefense::TowerRepository::reset()  {
    towers_.clear();
}