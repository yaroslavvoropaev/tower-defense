#pragma once

#include <cstddef>

namespace TowerDefense {
    /**
     * @brief Интерфейс для объектов, поддерживающих экономические операции.
     *
     * IEconomyable определяет базовый интерфейс для управления золотом (ресурсами)
     * игровых объектов. Реализуется классами, которые могут получать и тратить ресурсы.
     */
    class IEconomyable {
    public:
        /**
         * @brief Возвращает текущее количество золота.
         * @return Количество золота у объекта.
         */
        [[nodiscard]] virtual size_t get_gold() const = 0;

        /**
         * @brief Добавляет золото объекту.
         * @param amount Количество добавляемого золота.
         */
        virtual void add_gold(size_t amount) = 0;

        /**
         * @brief Вычитает золото у объекта.
         * @param amount Количество вычитаемого золота.
         */
        virtual void subtract_gold(size_t amount) = 0;

        /**
         * @brief Виртуальный деструктор для обеспечения корректного наследования.
         */
        virtual ~IEconomyable() = default;
    };
}