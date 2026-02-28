#include "CastleDTOMapper.h"


TowerDefense::CastleDTO TowerDefense::CastleDTOMapper::transform(const ICastle *castle) {
    CastleDTO dto {castle->get_ID(), castle->get_name(), castle->get_health(), castle->get_max_health(), castle->get_gold(),
                    castle->get_position().x_, castle->get_position().y_};
    return dto;
}


