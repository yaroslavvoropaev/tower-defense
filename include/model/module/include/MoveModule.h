#pragma once

#include "Point.h"
#include <atomic>

namespace TowerDefense {
    /**
     * @brief Модуль управления перемещением для игровых объектов.
     *
     * MoveModule отвечает за хранение позиции, скорости и состояния
     * перемещения объекта. Учитывает замедления и обеспечивает доступ
     * как к логическим координатам, так и к пиксельным для отображения.
     */
    class MoveModule {
        float current_speed_;           ///< Базовая скорость объекта
        bool is_move_ = true;           ///< Флаг возможности перемещения
        std::atomic<int> decelerationC_ {}; ///< Величина замедления (в процентах)
        Point position_;                ///< Логическая позиция на игровом поле
        float x_pixels_ = 0;            ///< X-координата в пикселях для отображения
        float y_pixels_ = 0;            ///< Y-координата в пикселях для отображения

    public:
        /**
         * @brief Конструктор модуля перемещения.
         *
         * @param start_speed Начальная скорость объекта.
         * @param start_position Начальная логическая позиция.
         * @param x_pixels Начальная X-координата в пикселях.
         * @param y_pixels Начальная Y-координата в пикселях.
         */
        MoveModule(float start_speed, const Point &start_position, float x_pixels, float y_pixels) : current_speed_(start_speed), position_(start_position),
              x_pixels_(x_pixels), y_pixels_(y_pixels) {}
        /**
         * @brief Конструктор по умолчанию.
         */
        MoveModule() = default;
        /**
         * @brief Устанавливает Y-координату в пикселях для отображения.
         *
         * @param y_pixels Новая Y-координата в пикселях.
         */
        void set_y_pixels(float y_pixels);

        /**
         * @brief Устанавливает X-координату в пикселях для отображения.
         *
         * @param x_pixels Новая X-координата в пикселях.
         */
        void set_x_pixels(float x_pixels);

        /**
         * @brief Возвращает X-координату в пикселях для отображения.
         *
         * @return Текущая X-координата в пикселях.
         */
        [[nodiscard]] float get_x_pixels() const;

        /**
         * @brief Возвращает Y-координату в пикселях для отображения.
         *
         * @return Текущая Y-координата в пикселях.
         */
        [[nodiscard]] float get_y_pixels() const;

        /**
         * @brief Возвращает текущую скорость с учетом замедлений.
         *
         * Скорость вычисляется по формуле: current_speed * (1 - decelerationC_ * 0.01).
         * Если результат отрицательный, возвращается 0.
         *
         * @return Текущая скорость объекта.
         */
        [[nodiscard]] float get_current_speed() const;

        /**
         * @brief Устанавливает логическую позицию объекта.
         *
         * Логическая позиция используется для игровой логики и расчетов пути.
         *
         * @param point Новая позиция.
         */
        void set_position(const Point &point);

        /**
         * @brief Возвращает текущую логическую позицию.
         *
         * @return Текущая позиция объекта.
         */
        [[nodiscard]] Point get_position() const;

        /**
         * @brief Изменяет уровень замедления объекта.
         *
         * Положительное значение увеличивает замедление, отрицательное - уменьшает.
         * Замедление влияет на текущую скорость через метод get_current_speed().
         *
         * @param deceleration Изменение замедления (может быть положительным или отрицательным).
         */
        void change_deceleration(int deceleration);
    };
}