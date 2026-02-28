#pragma once

#include "IEffect.h"

namespace TowerDefense {
    /**
     * @brief Эффект уязвимости, увеличивающий получаемый врагом урон.
     *
     * WeaknessEffect увеличивает урон, получаемый врагом от атак,
     * на определенный процент в течение заданного времени.
     */
    class WeaknessEffect final : public IEffect {
        int magnitude_;         ///< Процент увеличения получаемого урона
        float duration_;        ///< Длительность эффекта в секундах
        bool is_finished_ = false; ///< Флаг завершения эффекта

    public:
        /**
         * @brief Конструктор эффекта уязвимости.
         *
         * @param magnitude Процент увеличения получаемого урона.
         * @param duration Длительность эффекта в секундах.
         */
        WeaknessEffect(int magnitude, float duration)
            : magnitude_(magnitude), duration_(duration) {}

        /**
         * @brief Применяет эффект уязвимости к врагу.
         *
         * Увеличивает уязвимость врага к урону на указанный процент.
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

        ~WeaknessEffect() override = default;
    };
}