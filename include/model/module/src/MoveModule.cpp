#include "MoveModule.h"




TowerDefense::Point TowerDefense::MoveModule::get_position() const {
    return position_;
}

void TowerDefense::MoveModule::set_position(const Point &point) {
    position_ = point;
}



void TowerDefense::MoveModule::change_deceleration(int deceleration) {
    decelerationC_ += deceleration;
}


float TowerDefense::MoveModule::get_current_speed() const {
    float tmp = current_speed_ * (1.0f - static_cast<float>(decelerationC_) * 0.01f);
    if (tmp < 0) {
        tmp = 0;
    }
    return tmp;
}

void TowerDefense::MoveModule::set_y_pixels(float y_pixels) {
    y_pixels_ = y_pixels;
}


void TowerDefense::MoveModule::set_x_pixels(float x_pixels)  {
    x_pixels_ = x_pixels;
}


float TowerDefense::MoveModule::get_x_pixels() const {
    return x_pixels_;
}

float TowerDefense::MoveModule::get_y_pixels() const {
    return y_pixels_;
}