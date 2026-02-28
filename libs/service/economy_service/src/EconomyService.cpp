#include "EconomyService.h"

#include <iostream>


bool TowerDefense::EconomyService::upgrade(ID id) {
    auto tower = tower_repository_.get(id);
    auto castle = castle_repository_.get();
    size_t current_level = tower->get_level();
    auto upgrade_info = level_up_map_.at(typeid(*tower));

    if (upgrade_info.size() == current_level || castle->get_gold() < upgrade_info.at(current_level).cost ) {
        return false;
    }
    castle->subtract_gold(upgrade_info.at(current_level).cost);
    auto visitor = visitors_.at(typeid(*tower)).get();
    tower->accept_upgrade_visitor(*visitor, upgrade_info[current_level]);
    tower->set_level(current_level + 1);

    return true;
}

void TowerDefense::EconomyService::add_visitor(std::type_index type, std::unique_ptr<IUpgradeVisitor> visitor) {
    visitors_.emplace(type, std::move(visitor));
}

