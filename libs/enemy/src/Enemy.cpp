#include "Enemy.h"

void TowerDefense::Enemy::set_position(const Point &vector) {
    move_module_.set_position(vector);
}

TowerDefense::Point TowerDefense::Enemy::get_position() const {
    return move_module_.get_position();
}


float TowerDefense::Enemy::get_x_pixels() const {
    return move_module_.get_x_pixels();
}

float TowerDefense::Enemy::get_y_pixels() const {
    return move_module_.get_y_pixels();
}


void TowerDefense::Enemy::set_x_pixels(float x_pixels) {
    move_module_.set_x_pixels(x_pixels);
}

void TowerDefense::Enemy::set_y_pixels(float y_pixels) {
    move_module_.set_y_pixels(y_pixels);
}



float TowerDefense::Enemy::get_speed() const {
    return move_module_.get_current_speed();
}

void TowerDefense::Enemy::change_deceleration(int deceleration) {
    move_module_.change_deceleration(deceleration);
}


//name_module
std::string TowerDefense::Enemy::get_name() const {
    return name_;
}


//health_module
float TowerDefense::Enemy::get_health() const {
    return health_module_.get_current_health();
}

float TowerDefense::Enemy::get_max_health() const {
    return health_module_.get_max_health();
}


void TowerDefense::Enemy::take_damage(float damage) {
    health_module_.take_damage(damage);
}


void TowerDefense::Enemy::change_weakness(int weakness) {
    health_module_.change_weakness(weakness);
}

void TowerDefense::Enemy::update(float dt) {
    effect_module_.all_update(*this, dt);
}

//effect_module
void TowerDefense::Enemy::add_effect(std::unique_ptr<IEffect> effect) {
    effect_module_.add_effect(*this, std::move(effect));
}

//gold
size_t TowerDefense::Enemy::get_gold() const {
    return gold_;
}


TowerDefense::ID TowerDefense::Enemy::get_ID() const {
    return id_;
}

void TowerDefense::Enemy::set_ID(ID id) {
    id_ = id;
}

std::unique_ptr<TowerDefense::IEnemy> TowerDefense::Enemy::clone() {
    return std::make_unique<Enemy>(id_, name_, gold_, get_health(), get_max_health(), get_speed(), get_position(), get_x_pixels(), get_y_pixels());
}