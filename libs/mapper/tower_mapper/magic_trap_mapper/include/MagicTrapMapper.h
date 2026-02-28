#pragma once

#include "ITowerMapper.h"
#include "IStrategyRepository.h"
#include "IEffectFactory.h"

namespace TowerDefense {
    /**
     * @brief Конкретная реализация маппера для создания магических ловушек из DTO.
     *
     * MagicTrapMapper создает объекты типа ITower (конкретно MagicTrap)
     * на основе данных из TowerDTO. Использует репозиторий стратегий для
     * получения объектов стратегий и фабрику эффектов для создания эффектов.
     */
    class MagicTrapMapper final : public ITowerMapper {
        IStrategyRepository &strategy_repository_; ///< Репозиторий стратегий
        IEffectFactory &effect_factory_; ///< Фабрика эффектов

    public:
        /**
         * @brief Конструктор маппера магических ловушек.
         *
         * @param strategy_repository Репозиторий стратегий для получения объектов стратегий.
         * @param effect_factory Фабрика эффектов для создания эффектов.
         */
        explicit MagicTrapMapper(IStrategyRepository &strategy_repository, IEffectFactory &effect_factory)
            : strategy_repository_(strategy_repository), effect_factory_(effect_factory) {}

        /**
         * @brief Создает объект магической ловушки на основе DTO.
         *
         * Использует данные из DTO для инициализации нового объекта MagicTrap,
         * включая получение стратегии из репозитория и создание эффекта из фабрики.
         *
         * @param dto Объект передачи данных с параметрами ловушки.
         * @return std::unique_ptr<ITower> Умный указатель на созданную магическую ловушку.
         */
        std::unique_ptr<ITower> transform(const TowerDTO &dto) override;

        /**
         * @brief Деструктор маппера.
         */
        ~MagicTrapMapper() override = default;
    };
}