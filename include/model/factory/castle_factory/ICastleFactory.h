#pragma once

#include <memory>
#include "ICastle.h"

namespace TowerDefense {
    /**
     * @brief Интерфейс фабрики для создания объектов замков.
     *
     * ICastleFactory реализует паттерн "Фабричный метод", инкапсулируя логику
     * создания объектов типа ICastle. Позволяет создавать различные типы замков
     * без явного указания конкретных классов.
     */
    class ICastleFactory {
    public:
        /**
         * @brief Создает новый объект замка.
         *
         * @return std::unique_ptr<ICastle> Умный указатель на созданный замок.
         * @note Конкретный тип создаваемого замка определяется реализацией фабрики.
         */
        [[nodiscard]] virtual std::unique_ptr<ICastle> create_castle() const = 0;

        /**
         * @brief Виртуальный деструктор для корректного наследования.
         */
        virtual ~ICastleFactory() = default;
    };
}