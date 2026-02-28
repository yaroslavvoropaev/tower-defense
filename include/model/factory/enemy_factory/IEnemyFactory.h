#pragma once

#include "IEnemy.h"
#include <memory>

namespace TowerDefense {
    /**
     * @brief Интерфейс фабрики для создания врагов.
     *
     * IEnemyFactory реализует паттерн "Фабричный метод", инкапсулируя логику
     * создания объектов типа IEnemy. Позволяет создавать различные типы врагов
     * с заданными характеристиками без явного указания конкретных классов.
     */
    class IEnemyFactory {
    public:
        /**
         * @brief Создает нового врага.
         *
         * @return std::unique_ptr<IEnemy> Умный указатель на созданного врага.
         * @note Конкретный тип создаваемого врага определяется реализацией фабрики.
         */
        [[nodiscard]] virtual std::unique_ptr<IEnemy> create_enemy() const = 0;

        /**
         * @brief Виртуальный деструктор для корректного наследования.
         */
        virtual ~IEnemyFactory() = default;
    };
}