#pragma once

#include "ICastle.h"
#include "dto.h"

namespace TowerDefense {
    /**
     * @brief Интерфейс маппера для преобразования объекта замка в DTO (Data Transfer Object).
     *
     * ICastleDTOMapper отвечает за преобразование объектов типа ICastle в
     * соответствующие объекты типа CastleDTO. Этот паттерн используется для
     * отделения бизнес-логики от представления данных и упрощения сериализации.
     */
    class ICastleDTOMapper {
    public:
        /**
         * @brief Преобразует объект замка в DTO.
         *
         * @param castle Указатель на объект замка для преобразования.
         * @return CastleDTO - объект передачи данных, содержащий состояние замка.
         * @note Вызывающая сторона сохраняет владение объектом castle.
         */
        virtual CastleDTO transform(const ICastle *castle) = 0;

        /**
         * @brief Виртуальный деструктор для обеспечения корректного удаления производных классов.
         */
        virtual ~ICastleDTOMapper() = default;
    };
}