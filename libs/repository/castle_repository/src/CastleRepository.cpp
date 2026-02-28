#include "CastleRepository.h"

TowerDefense::ICastle *TowerDefense::CastleRepository::get() {
    return castle_.get();
}

void TowerDefense::CastleRepository::add_castle(std::unique_ptr<ICastle> castle) {
    castle_ = std::move(castle);
}