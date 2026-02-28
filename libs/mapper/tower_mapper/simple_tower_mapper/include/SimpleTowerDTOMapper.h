#pragma once

#include "IStrategyRepository.h"
#include "ITowerDTOMapper.h"

namespace TowerDefense {
    /**
     * @brief Конкретная реализация маппера для преобразования простых башен в DTO.
     *
     * SimpleTowerDTOMapper преобразует объекты типа ITower (конкретно SimpleTower)
     * в объекты типа TowerDTO. Использует репозиторий стратегий для получения
     * имени стратегии.
     */
    class SimpleTowerDTOMapper final : public ITowerDTOMapper {
        IStrategyRepository &strategy_repository_; ///< Репозиторий стратегий

    public:
        /**
         * @brief Конструктор маппера простых башен.
         *
         * @param strategy_repository Репозиторий стратегий для получения имен стратегий.
         */
        explicit SimpleTowerDTOMapper(IStrategyRepository &strategy_repository) : strategy_repository_(strategy_repository) {};
        /**
         * @brief Преобразует объект простой башни в DTO.
         *
         * Извлекает все необходимые данные из объекта башни, включая
         * информацию о стратегии, и создает DTO.
         *
         * @param tower Указатель на объект башни для преобразования.
         * @return TowerDTO Объект передачи данных с состоянием башни.
         */
        TowerDTO transform(const ITower *tower) override;

        /**
         * @brief Деструктор маппера.
         */
        ~SimpleTowerDTOMapper() override = default;
    };
}