#include "GameFiled.h"


size_t TowerDefense::GameFiled::get_width() const {
    return field.cols();
}

size_t TowerDefense::GameFiled::get_height() const {
    return field.rows();
}

TowerDefense::Cell TowerDefense::GameFiled::get_cell(size_t row, size_t col) const {
    return field[row][col];
}

void TowerDefense::GameFiled::set_cell(size_t row, size_t col, const Cell &cell) {
    field[row][col] = cell;
}