#pragma once

#include "IEnemy.h"
#include "HealthModule.h"
#include "EffectModule.h"
#include "MoveModule.h"

namespace TowerDefense {

    /**
     * @brief Конкретная реализация врага в игре Tower Defense.
     *
     * Класс Enemy является финальной реализацией интерфейса IEnemy.
     * Использует модульный подход: HealthModule для здоровья, EffectModule
     * для эффектов и MoveModule для перемещения.
     */
    class Enemy final : public IEnemy {
        ID id_{};                     ///< Уникальный идентификатор врага
        std::string name_;          ///< Имя врага
        size_t gold_{};               ///< Количество золота за убийство
        HealthModule health_module_; ///< Модуль управления здоровьем
        EffectModule effect_module_ {}; ///< Модуль управления эффектами
        MoveModule move_module_;    ///< Модуль управления перемещением

    public:
        /**
         * @brief Конструктор врага.
         *
         * @param id Уникальный идентификатор врага.
         * @param name Имя врага.
         * @param gold Количество золота за убийство.
         * @param health Начальное здоровье врага.
         * @param max_health Максимальное здоровье врага.
         * @param speed Скорость перемещения врага.
         * @param start_position Начальная позиция врага.
         * @param x_pixels X-координата в пикселях для отображения.
         * @param y_pixels Y-координата в пикселях для отображения.
         */
        Enemy(ID id, const std::string &name, size_t gold, float health, float max_health, float speed, const Point &start_position, float x_pixels, float y_pixels)
            : id_(id), name_(name), gold_(gold), health_module_(health, max_health),move_module_(speed, start_position, x_pixels, y_pixels) {}

        /**
         * @brief Устанавливает X-координату в пикселях для отображения.
         *
         * @param x_pixels Новая X-координата в пикселях.
         */
        void set_x_pixels(float x_pixels) override;

        /**
         * @brief Устанавливает Y-координату в пикселях для отображения.
         *
         * @param y_pixels Новая Y-координата в пикселях.
         */
        void set_y_pixels(float y_pixels) override;

        /**
         * @brief Возвращает X-координату в пикселях для отображения.
         *
         * @return float X-координата в пикселях.
         */
        [[nodiscard]] float get_x_pixels() const override;

        /**
         * @brief Возвращает Y-координату в пикселях для отображения.
         *
         * @return float Y-координата в пикселях.
         */
        [[nodiscard]] float get_y_pixels() const override;

        /**
         * @brief Устанавливает логическую позицию врага.
         *
         * @param vector Новая позиция врага.
         */
        void set_position(const Point &vector) override;

        /**
         * @brief Возвращает текущую логическую позицию врага.
         *
         * @return Point Текущая позиция врага.
         */
        [[nodiscard]] Point get_position() const override;

        /**
         * @brief Возвращает текущую скорость врага с учетом замедлений.
         *
         * @return float Текущая скорость врага.
         */
        [[nodiscard]] float get_speed() const override;

        /**
         * @brief Изменяет уровень замедления врага.
         *
         * @param deceleration Изменение замедления.
         */
        void change_deceleration(int deceleration) override;

        /**
         * @brief Обновляет состояние врага.
         *
         * @param dt Время, прошедшее с предыдущего обновления.
         */
        void update(float dt) override;

        /**
         * @brief Возвращает имя/тип врага.
         *
         * @return std::string Имя врага.
         */
        [[nodiscard]] std::string get_name() const override;

        /**
         * @brief Наносит урон врагу.
         *
         * @param damage Величина наносимого урона.
         */
        void take_damage(float damage) override;

        /**
         * @brief Изменяет уязвимость врага.
         *
         * @param weakness Изменение уязвимости.
         */
        void change_weakness(int weakness) override;

        /**
         * @brief Возвращает текущее здоровье врага.
         *
         * @return float Текущее здоровье.
         */
        [[nodiscard]] float get_health() const override;

        /**
         * @brief Возвращает максимальное здоровье врага.
         *
         * @return float Максимальное здоровье.
         */
        [[nodiscard]] float get_max_health() const override;
        /**
         * @brief Добавляет эффект врагу.
         *
         * @param effect Умный указатель на эффект для добавления.
         */
        void add_effect(std::unique_ptr<IEffect> effect) override;

        /**
         * @brief Возвращает количество золота за убийство врага.
         *
         * @return size_t Количество золота.
         */
        [[nodiscard]] size_t get_gold() const override;

        /**
         * @brief Возвращает уникальный идентификатор врага.
         *
         * @return ID Идентификатор врага.
         */
        [[nodiscard]] ID get_ID() const override;

        /**
         * @brief Устанавливает уникальный идентификатор врага.
         *
         * @param id Новый идентификатор.
         */
        void set_ID(ID id) override;

        /**
         * @brief Создает глубокую копию врага.
         *
         * Реализует паттерн "Прототип".
         *
         * @return std::unique_ptr<IEnemy> Умный указатель на копию врага.
         */
        std::unique_ptr<IEnemy> clone() override;

        /**
         * @brief Деструктор врага.
         */
        ~Enemy() override = default;
    };
}