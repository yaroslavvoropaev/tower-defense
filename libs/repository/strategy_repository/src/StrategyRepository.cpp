#include "StrategyRepository.h"

#include <iostream>


void TowerDefense::StrategyRepository::add_strategy(std::string name, std::unique_ptr<IStrategy> strategy) {
    strategy_types_.emplace(typeid(*strategy), name);
    strategies_.emplace(name, std::move(strategy));
}


TowerDefense::IStrategy *TowerDefense::StrategyRepository::get_strategy(const std::string &name) const {
    return strategies_.at(name).get();
}

std::string TowerDefense::StrategyRepository::get_strategy_name(IStrategy *strategy) const {
    return strategy_types_.at(typeid(*strategy));
}
