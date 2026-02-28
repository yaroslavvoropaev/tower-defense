#pragma once

#include "IStrategy.h"

namespace TowerDefense {
    /**
     * @brief Интерфейс репозитория для управления стратегиями.
     *
     * IStrategyRepository определяет методы для регистрации и получения
     * стратегий. Стратегии
     * идентифицируются по строковым именам.
     */
    class IStrategyRepository {
    public:
        /**
         * @brief Добавляет стратегию в репозиторий.
         *
         * @param name Имя стратегии для регистрации.
         * @param strategy Умный указатель на объект стратегии.
         *                 Владение объектом передается репозиторию.
         */
        virtual void add_strategy(std::string name, std::unique_ptr<IStrategy> strategy) = 0;

        /**
         * @brief Возвращает стратегию по имени.
         *
         * @param name Имя стратегии.
         * @return IStrategy* Указатель на объект стратегии (не передает владение).
         */
        [[nodiscard]] virtual IStrategy *get_strategy(const std::string &name) const = 0;

        /**
         * @brief Возвращает имя стратегии по объекту.
         *
         * @param strategy Указатель на объект стратегии.
         * @return std::string Имя стратегии.
         */
        [[nodiscard]] virtual std::string get_strategy_name(IStrategy *strategy) const = 0;

        virtual ~IStrategyRepository() = default;
    };
}