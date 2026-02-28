#pragma once

#include <memory>

#include "ICastle.h"
#include "dto.h"

namespace TowerDefense {
    /**
     * @brief Интерфейс маппера для создания объектов замка из DTO (Data Transfer Object).
     *
     * ICastleMapper отвечает за создание объектов типа ICastle на основе
     * данных из CastleDTO. Этот паттерн используется для инкапсуляции логики
     * создания объектов и отделения слоя данных от бизнес-логики.
     */
    class ICastleMapper {
    public:
        /**
         * @brief Создает объект замка на основе DTO.
         *
         * @param dto Объект передачи данных, содержащий параметры для создания замка.
         * @return std::unique_ptr<ICastle> - умный указатель на созданный объект замка.
         * @note Возвращаемый объект полностью инкапсулирован и управляется умным указателем.
         */
        virtual std::unique_ptr<ICastle> transform(const CastleDTO &dto) = 0;

        /**
         * @brief Виртуальный деструктор для обеспечения корректного удаления производных классов.
         */
        virtual ~ICastleMapper() = default;
    };
}