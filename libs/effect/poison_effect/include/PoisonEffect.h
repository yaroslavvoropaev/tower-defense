#pragma once

#include "IEffect.h"

#include <chrono>

namespace TowerDefense {
    /**
     * @brief Эффект отравления, наносящий периодический урон врагу.
     *
     * PoisonEffect наносит урон врагу в течение определенного времени.
     * Урон применяется периодически с заданной интенсивностью.
     */
    class PoisonEffect final : public IEffect {
        float magnitude_;      ///< Величина урона за единицу времени
        float duration_;       ///< Общая длительность эффекта в секундах
        bool is_finished_ = false; ///< Флаг завершения эффекта

    public:
        /**
         * @brief Конструктор эффекта отравления.
         *
         * @param magnitude Величина урона в секунду.
         * @param duration Длительность эффекта в секундах.
         */
        PoisonEffect(float magnitude, float duration)
            : magnitude_(magnitude), duration_(duration) {}

        /**
         * @brief Применяет начальное действие эффекта к врагу.
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
         * Наносит периодический урон врагу и обновляет оставшееся время действия.
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

        ~PoisonEffect() override = default;
    };
}