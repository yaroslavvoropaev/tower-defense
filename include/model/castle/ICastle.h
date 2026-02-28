#pragma once

#include "IEconomyable.h"
#include "Point.h"
#include "id.h"

#include <string>

namespace TowerDefense {
    /**
     * @brief Интерфейс, представляющий замок в игре Tower Defense.
     *
     * ICastle определяет основные свойства и поведение замка, который является
     * ключевым защищаемым объектом на игровом поле. Замок имеет здоровье, позицию,
     * идентификатор и поддерживает экономические операции через наследование от IEconomyable.
     */
    class ICastle : public IEconomyable {
    public:
        /**
         * @brief Возвращает текущее здоровье замка.
         * @return Текущее значение здоровья.
         */
        [[nodiscard]] virtual float get_health() const = 0;

        /**
         * @brief Возвращает максимальное здоровье замка.
         * @return Максимальное значение здоровья.
         */
        [[nodiscard]] virtual float get_max_health() const = 0;

        /**
         * @brief Устанавливает здоровье замка.
         * @param health Новое значение здоровья.
         */
        virtual void set_health(float health) = 0;

        /**
         * @brief Наносит урон замку.
         * @param damage Величина наносимого урона.
         */
        virtual void take_damage(float damage) = 0;

        /**
         * @brief Возвращает позицию замка на игровом поле.
         * @return Координаты позиции замка.
         */
        [[nodiscard]] virtual Point get_position() const = 0;

        /**
         * @brief Возвращает имя замка.
         * @return Строка с именем замка.
         */
        [[nodiscard]] virtual std::string get_name() const = 0;

        /**
         * @brief Возвращает уникальный идентификатор замка.
         * @return Идентификатор замка.
         */
        [[nodiscard]] virtual ID get_ID() const = 0;

        /**
         * @brief Устанавливает уникальный идентификатор замка.
         * @param id Новый идентификатор.
         */
        virtual void set_ID(ID id) = 0;

        /**
         * @brief Виртуальный деструктор для корректного наследования.
         */
        ~ICastle() override = default;
    };
}