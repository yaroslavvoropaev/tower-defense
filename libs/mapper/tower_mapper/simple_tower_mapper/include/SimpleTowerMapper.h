#pragma once

#include "ITowerMapper.h"
#include "IStrategyRepository.h"

namespace TowerDefense {
    /**
     * @brief Конкретная реализация маппера для создания простых башен из DTO.
     *
     * SimpleTowerMapper создает объекты типа ITower (конкретно SimpleTower)
     * на основе данных из TowerDTO. Использует репозиторий стратегий для
     * получения объектов стратегий.
     */
    class SimpleTowerMapper final : public ITowerMapper {
        IStrategyRepository &strategy_repository_; ///< Репозиторий стратегий

    public:
        /**
         * @brief Конструктор маппера простых башен.
         *
         * @param strategy_repository Репозиторий стратегий для получения объектов стратегий.
         */
        explicit SimpleTowerMapper(IStrategyRepository &strategy_repository)
            : strategy_repository_(strategy_repository) {}

        /**
         * @brief Создает объект простой башни на основе DTO.
         *
         * Использует данные из DTO для инициализации нового объекта SimpleTower,
         * включая получение стратегии из репозитория.
         *
         * @param dto Объект передачи данных с параметрами башни.
         * @return std::unique_ptr<ITower> Умный указатель на созданную простую башню.
         */
        std::unique_ptr<ITower> transform(const TowerDTO &dto) override;

        /**
         * @brief Деструктор маппера.
         */
        ~SimpleTowerMapper() override = default;
    };
}