#include "ID_service.h"


TowerDefense::ID TowerDefense::ID_service::get_id()  {
    counter_++;
    return counter_;
}

void TowerDefense::ID_service::set_id(ID id) {
    counter_ = id;
}