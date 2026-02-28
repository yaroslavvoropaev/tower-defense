#pragma once

#include "AbstractTower.h"
#include "IAttackVisitor.h"

namespace TowerDefense {

    /**
     * @class MagicTrapAttackVisitor
     * @brief Посетитель для обработки активации магической ловушки.
     *
     * Реализует паттерн Посетитель для обработки логики активации магической ловушки.
     * Определяет, как ловушка применяет эффекты к целям без нанесения прямого урона.
     */
    class MagicTrapAttackVisitor : public IAttackVisitor {
    public:
        /**
         * @brief Конструктор по умолчанию.
         */
        MagicTrapAttackVisitor() = default;

        /**
         * @brief Обрабатывает активацию магической ловушки.
         * @param tower Ссылка на ловушку, которая активируется.
         * @param dt Время, прошедшее с предыдущего обновления.
         * @return Информация об атаке.
         */
        AttackInfo visit(ITower &tower, float dt) override;

        /**
         * @brief Деструктор по умолчанию.
         */
        ~MagicTrapAttackVisitor() override = default;
    };
}