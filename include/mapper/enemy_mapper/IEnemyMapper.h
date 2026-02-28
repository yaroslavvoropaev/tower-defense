#pragma once

#include <memory>

#include "IEnemy.h"
#include "dto.h"

namespace TowerDefense {
    /**
     * @brief Интерфейс маппера для создания объектов врага из DTO (Data Transfer Object).
     *
     * IEnemyMapper отвечает за создание объектов типа IEnemy на основе данных из EnemyDTO.
     * Инкапсулирует логику инициализации врагов с учетом их типа, характеристик
     * и других параметров, определенных в DTO.
     */
    class IEnemyMapper {
    public:
        /**
         * @brief Создает объект врага на основе DTO.
         *
         * @param dto Объект передачи данных, содержащий параметры для создания врага.
         * @return std::unique_ptr<IEnemy> - умный указатель на созданный объект врага.
         * @note Возвращаемый объект полностью инкапсулирован и управляется умным указателем.
         */
        virtual std::unique_ptr<IEnemy> transform(const EnemyDTO &dto) = 0;

        /**
         * @brief Виртуальный деструктор для обеспечения корректного удаления производных классов.
         */
        virtual ~IEnemyMapper() = default;
    };
}