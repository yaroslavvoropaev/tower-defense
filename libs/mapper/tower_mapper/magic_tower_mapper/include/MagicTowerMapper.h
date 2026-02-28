#pragma once

#include "ITowerMapper.h"
#include "IStrategyRepository.h"
#include "IEffectFactory.h"

namespace TowerDefense {
    /**
     * @brief Конкретная реализация маппера для создания магических башен из DTO.
     *
     * MagicTowerMapper создает объекты типа ITower (конкретно MagicTower)
     * на основе данных из TowerDTO. Использует репозиторий стратегий для
     * получения объектов стратегий и фабрику эффектов для создания эффектов.
     */
    class MagicTowerMapper final : public ITowerMapper {
        IStrategyRepository &strategy_repository_; ///< Репозиторий стратегий
        IEffectFactory &effect_factory_; ///< Фабрика эффектов

    public:
        /**
         * @brief Конструктор маппера магических башен.
         *
         * @param strategy_repository Репозиторий стратегий для получения объектов стратегий.
         * @param effect_factory Фабрика эффектов для создания эффектов.
         */
        explicit MagicTowerMapper(IStrategyRepository &strategy_repository, IEffectFactory &effect_factory)
            : strategy_repository_(strategy_repository), effect_factory_(effect_factory) {}

        /**
         * @brief Создает объект магической башни на основе DTO.
         *
         * Использует данные из DTO для инициализации нового объекта MagicTower,
         * включая получение стратегии из репозитория и создание эффекта из фабрики.
         *
         * @param dto Объект передачи данных с параметрами башни.
         * @return std::unique_ptr<ITower> Умный указатель на созданную магическую башню.
         */
        std::unique_ptr<ITower> transform(const TowerDTO &dto) override;

        /**
         * @brief Деструктор маппера.
         */
        ~MagicTowerMapper() override = default;
    };
}