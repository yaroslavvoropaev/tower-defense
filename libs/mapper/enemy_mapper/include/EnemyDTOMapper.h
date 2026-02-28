#pragma once

#include "IEnemyDTOMapper.h"

namespace TowerDefense {
    /**
     * @brief Конкретная реализация маппера для преобразования врагов в DTO.
     *
     * EnemyDTOMapper преобразует объекты типа IEnemy в объекты типа EnemyDTO.
     */
    class EnemyDTOMapper final : public IEnemyDTOMapper {
    public:
        /**
         * @brief Конструктор маппера.
         */
        EnemyDTOMapper() = default;

        /**
         * @brief Преобразует объект врага в DTO.
         *
         * Извлекает все необходимые данные из объекта врага и создает DTO.
         *
         * @param enemy Указатель на объект врага для преобразования.
         * @return EnemyDTO Объект передачи данных с состоянием врага.
         */
        EnemyDTO transform(const IEnemy *enemy) override;

        /**
         * @brief Деструктор маппера.
         */
        ~EnemyDTOMapper() override = default;
    };
}