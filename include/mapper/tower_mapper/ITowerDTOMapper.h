#pragma once

#include "AbstractTower.h"
#include "dto.h"

namespace TowerDefense {
    /**
     * @brief Интерфейс маппера для преобразования объекта башни в DTO (Data Transfer Object).
     *
     * ITowerDTOMapper отвечает за преобразование объектов типа ITower в
     * соответствующие объекты типа TowerDTO. Используется для сериализации
     * состояния башен, передачи данных между слоями приложения или сохранения
     * игрового состояния.
     */
    class ITowerDTOMapper {
    public:
        /**
         * @brief Преобразует объект башни в DTO.
         *
         * @param tower Указатель на объект башни для преобразования.
         * @return TowerDTO - объект передачи данных, содержащий состояние башни.
         * @note Вызывающая сторона сохраняет владение объектом tower.
         */
        virtual TowerDTO transform(const ITower *tower) = 0;

        /**
         * @brief Виртуальный деструктор для обеспечения корректного удаления производных классов.
         */
        virtual ~ITowerDTOMapper() = default;
    };
}