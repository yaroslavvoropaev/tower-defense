#pragma once

#include "IEffect.h"

#include <chrono>

namespace TowerDefense {
    /**
     * @brief Эффект замедления, уменьшающий скорость врага.
     *
     * SlowEffect уменьшает скорость передвижения врага на определенный процент
     * в течение заданного времени.
     */
    class SlowEffect final : public IEffect {
        int magnitude_;         ///< Процент замедления
        float duration_;        ///< Длительность эффекта в секундах
        bool is_finished_ = false; ///< Флаг завершения эффекта

    public:
        /**
         * @brief Конструктор эффекта замедления.
         *
         * @param magnitude Процент замедления.
         * @param duration Длительность эффекта в секундах.
         */
        SlowEffect(int magnitude, float duration)
            : magnitude_(magnitude), duration_(duration) {}

        /**
         * @brief Применяет замедление к врагу.
         *
         * Уменьшает скорость врага на указанный процент.
         *
         * @param enemy Ссылка на врага, к которому применяется эффект.
         */
        void apply_effect(IEnemy &enemy) override;

        /**
         * @brief Создает глубокую копию эффекта.
         *
         * @return std::unique_ptr<IEffect> Умный указатель на копию эффекта.
         */
        std::unique_ptr<IEffect> clone() override;

        /**
         * @brief Обновляет состояние эффекта с течением времени.
         *
         * Обновляет оставшееся время действия эффекта.
         *
         * @param enemy Ссылка на врага, на которого действует эффект.
         * @param dt Время, прошедшее с предыдущего обновления.
         */
        void update_effect(IEnemy &enemy, float dt) override;

        /**
         * @brief Проверяет, завершился ли эффект.
         *
         * @return true, если длительность эффекта истекла; иначе false.
         */
        bool is_finished() override;

        ~SlowEffect() override = default;
    };
}