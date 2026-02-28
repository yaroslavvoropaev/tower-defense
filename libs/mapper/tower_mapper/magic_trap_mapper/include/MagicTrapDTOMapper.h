#pragma once

#include "IEffectFactory.h"
#include "IStrategyRepository.h"
#include "ITowerDTOMapper.h"

namespace TowerDefense {
    /**
     * @brief Конкретная реализация маппера для преобразования магических ловушек в DTO.
     *
     * MagicTrapDTOMapper преобразует объекты типа ITower (конкретно MagicTrap)
     * в объекты типа TowerDTO. Использует репозиторий стратегий для получения
     * имени стратегии и фабрику эффектов для получения имени эффекта.
     */
    class MagicTrapDTOMapper final : public ITowerDTOMapper {
        IStrategyRepository &strategy_repository_; ///< Репозиторий стратегий
        IEffectFactory &effect_factory_; ///< Фабрика эффектов

    public:
        /**
         * @brief Конструктор маппера магических ловушек.
         *
         * @param strategy_repository Репозиторий стратегий для получения имен стратегий.
         * @param effect_factory Фабрика эффектов для получения имен эффектов.
         */
        explicit MagicTrapDTOMapper(IStrategyRepository &strategy_repository, IEffectFactory &effect_factory)
            : strategy_repository_(strategy_repository), effect_factory_(effect_factory) {};

        /**
         * @brief Преобразует объект магической ловушки в DTO.
         *
         * Извлекает все необходимые данные из объекта ловушки, включая
         * информацию о стратегии и эффекте, и создает DTO.
         *
         * @param tower Указатель на объект ловушки для преобразования.
         * @return TowerDTO Объект передачи данных с состоянием ловушки.
         */
        TowerDTO transform(const ITower *tower) override;

        /**
         * @brief Деструктор маппера.
         */
        ~MagicTrapDTOMapper() override = default;
    };
}