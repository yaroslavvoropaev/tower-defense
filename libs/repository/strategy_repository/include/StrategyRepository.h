#pragma once

#include "IStrategyRepository.h"

#include <unordered_map>
#include <string>
#include <memory>
#include <typeindex>

#include "ICastleRepository.h"
#include "IEnemyRepository.h"
#include "Weakest.h"
#include "Strongest.h"
#include "AllInRange.h"
#include "NearestToCastle.h"
#include "NearestToTower.h"

namespace TowerDefense {
    /**
     * @brief Конкретная реализация репозитория для управления стратегиями.
     *
     * StrategyRepository хранит различные стратегии выбора целей для башен.
     * Каждая стратегия регистрируется под уникальным именем и может быть
     * получена по этому имени.
     */
    class StrategyRepository final : public IStrategyRepository {
        std::unordered_map<std::string, std::unique_ptr<IStrategy>> strategies_; ///< Хранилище стратегий
        std::unordered_map<std::type_index, std::string> strategy_types_; ///< Соответствие тип-имя

    public:
        /**
         * @brief Конструктор репозитория стратегий.
         */
        StrategyRepository() = default;

        /**
         * @brief Добавляет стратегию в репозиторий.
         *
         * @param name Имя стратегии для регистрации.
         * @param strategy Умный указатель на объект стратегии.
         */
        void add_strategy(std::string name, std::unique_ptr<IStrategy> strategy) override;

        /**
         * @brief Возвращает стратегию по имени.
         *
         * @param name Имя стратегии.
         * @return IStrategy* Указатель на объект стратегии (не передает владение).
         */
        [[nodiscard]] IStrategy *get_strategy(const std::string &name) const override;

        /**
         * @brief Возвращает имя стратегии по объекту.
         *
         * @param strategy Указатель на объект стратегии.
         * @return std::string Имя стратегии.
         */
        [[nodiscard]] std::string get_strategy_name(IStrategy *strategy) const override;

        /**
         * @brief Деструктор репозитория.
         */
        ~StrategyRepository() override = default;
    };
}