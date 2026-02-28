#pragma once

#include "IEnemyMapper.h"

namespace TowerDefense {
    /**
     * @brief Конкретная реализация маппера для создания врагов из DTO.
     *
     * EnemyMapper создает объекты типа IEnemy на основе данных из EnemyDTO.
     */
    class EnemyMapper final : public IEnemyMapper {
    public:
        /**
         * @brief Конструктор маппера.
         */
        EnemyMapper() = default;

        /**
         * @brief Создает объект врага на основе DTO.
         *
         * Использует данные из DTO для инициализации нового объекта врага.
         *
         * @param dto Объект передачи данных с параметрами врага.
         * @return std::unique_ptr<IEnemy> Умный указатель на созданный объект врага.
         */
        std::unique_ptr<IEnemy> transform(const EnemyDTO &dto) override;

        /**
         * @brief Деструктор маппера.
         */
        ~EnemyMapper() override = default;
    };
}