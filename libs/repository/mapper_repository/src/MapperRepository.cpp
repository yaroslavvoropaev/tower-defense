#include "MapperRepository.h"


void TowerDefense::MapperRepository::add_castle_mapper(std::unique_ptr<ICastleMapper> mapper) {
    from_castle_dto_ = std::move(mapper);
}

void TowerDefense::MapperRepository::add_castle_dto_mapper(std::unique_ptr<ICastleDTOMapper> mapper) {
    from_castle_ = std::move(mapper);
}

void TowerDefense::MapperRepository::add_enemy_mapper(std::unique_ptr<IEnemyMapper> mapper) {
    from_enemy_dto_ = std::move(mapper);
}

void TowerDefense::MapperRepository::add_enemy_dto_mapper(std::unique_ptr<IEnemyDTOMapper> mapper) {
    from_enemy_ = std::move(mapper);
}


void TowerDefense::MapperRepository::add_tower_mapper(std::string name, std::unique_ptr<ITowerMapper> mapper) {
    from_tower_dto_.emplace(name, std::move(mapper));
}

void TowerDefense::MapperRepository::add_tower_dto_mapper(std::type_index type, std::unique_ptr<ITowerDTOMapper> mapper) {
    from_tower_.emplace(type, std::move(mapper));
}



std::unique_ptr<TowerDefense::IEnemy> TowerDefense::MapperRepository::dto_to_enemy(const EnemyDTO &enemy_dto) {
    return from_enemy_dto_->transform(enemy_dto);
}

TowerDefense::EnemyDTO TowerDefense::MapperRepository::enemy_to_dto(const IEnemy *enemy) {
    return from_enemy_->transform(enemy);
}

std::unique_ptr<TowerDefense::ICastle> TowerDefense::MapperRepository::dto_to_castle(const CastleDTO &castle_dto) {
    return from_castle_dto_->transform(castle_dto);
}

TowerDefense::CastleDTO TowerDefense::MapperRepository::castle_to_dto(const ICastle *castle) {
    return from_castle_->transform(castle);
}

std::unique_ptr<TowerDefense::ITower> TowerDefense::MapperRepository::dto_to_tower(const TowerDTO &tower_dto) {
    return from_tower_dto_.at(tower_dto.type)->transform(tower_dto);
}

TowerDefense::TowerDTO TowerDefense::MapperRepository::tower_to_dto(const ITower *tower) {
    return from_tower_.at(typeid(*tower))->transform(tower);
}


