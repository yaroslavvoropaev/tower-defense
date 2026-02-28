#pragma once

#include <memory>

#include "AbstractTower.h"
#include "dto.h"

namespace TowerDefense {
    /**
     * @brief Интерфейс маппера для создания объектов башни из DTO (Data Transfer Object).
     *
     * ITowerMapper отвечает за создание объектов типа ITower на основе данных из TowerDTO.
     * Инкапсулирует логику инициализации башен с учетом их типа, характеристик,
     * уровня улучшений и других параметров, определенных в DTO.
     */
    class ITowerMapper {
    public:
        /**
         * @brief Создает объект башни на основе DTO.
         *
         * @param dto Объект передачи данных, содержащий параметры для создания башни.
         * @return std::unique_ptr<ITower> - умный указатель на созданный объект башни.
         * @note Возвращаемый объект полностью инкапсулирован и управляется умным указателем.
         */
        virtual std::unique_ptr<ITower> transform(const TowerDTO &dto) = 0;

        /**
         * @brief Виртуальный деструктор для обеспечения корректного удаления производных классов.
         */
        virtual ~ITowerMapper() = default;
    };
}