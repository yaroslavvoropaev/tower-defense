
#include "Castle.h"


//health_module

float TowerDefense::Castle::get_health() const {
    return health_;
}

float TowerDefense::Castle::get_max_health() const {
    return max_health_;
}

void TowerDefense::Castle::set_health(float health) {
    health_ = health;
}

void TowerDefense::Castle::take_damage(float damage) {
    health_ -= damage;
}

std::string TowerDefense::Castle::get_name() const {
    return name_;
}

TowerDefense::Point TowerDefense::Castle::get_position() const {
    return position_;
}


//economy_module
void TowerDefense::Castle::add_gold(size_t gold) {
    gold_ += gold;
}

void TowerDefense::Castle::subtract_gold(size_t gold) {
    gold_ -= gold;
}
size_t TowerDefense::Castle::get_gold() const {
    return gold_;
}

//ID

TowerDefense::ID TowerDefense::Castle::get_ID() const {
    return id_;
}

void TowerDefense::Castle::set_ID(ID id)  {
    id_ = id;
}




