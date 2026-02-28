#pragma once

#include "Point.h"

namespace TowerDefense {
    /**
     * @brief Интерфейс для объектов, способных перемещаться.
     *
     * IMoveable определяет функциональность для управления позицией и
     * перемещением игровых объектов.
     */
    class IMoveable {
    public:
        virtual ~IMoveable() = default;

        /**
         * @brief Устанавливает позицию объекта.
         * @param point Новая позиция объекта.
         */
        virtual void set_position(const Point &point) = 0;

        /**
         * @brief Возвращает текущую позицию объекта.
         * @return Текущая позиция объекта.
         */
        [[nodiscard]] virtual Point get_position() const = 0;

        /**
         * @brief Возвращает скорость перемещения объекта.
         * @return Скорость объекта.
         */
        [[nodiscard]] virtual float get_speed() const = 0;

        /**
         * @brief Возвращает X-координату в пикселях для отображения.
         * @return X-координата в пикселях.
         */
        [[nodiscard]] virtual float get_x_pixels() const = 0;

        /**
         * @brief Возвращает Y-координату в пикселях для отображения.
         * @return Y-координата в пикселях.
         */
        [[nodiscard]] virtual float get_y_pixels() const = 0;

        /**
         * @brief Устанавливает X-координату в пикселях.
         * @param x_pixels Новая X-координата в пикселях.
         */
        virtual void set_x_pixels(float x_pixels) = 0;

        /**
         * @brief Устанавливает Y-координату в пикселях.
         * @param y_pixels Новая Y-координата в пикселях.
         */
        virtual void set_y_pixels(float y_pixels) = 0;

        /**
         * @brief Изменяет замедление объекта (например, от эффектов).
         * @param deceleration_value Величина замедления для изменения.
         */
        virtual void change_deceleration(int deceleration_value) = 0;
    };
}