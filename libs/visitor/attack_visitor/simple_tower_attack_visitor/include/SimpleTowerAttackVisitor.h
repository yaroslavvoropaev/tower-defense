#pragma once

#include "AbstractTower.h"
#include "IAttackVisitor.h"

namespace TowerDefense {

    /**
     * @class SimpleTowerAttackVisitor
     * @brief Посетитель для обработки атаки простой башни.
     *
     * Реализует паттерн Посетитель для обработки логики атаки простой башни.
     * Определяет, как простая башня наносит урон целям без дополнительных эффектов.
     */
    class SimpleTowerAttackVisitor : public IAttackVisitor {
    public:
        /**
         * @brief Конструктор по умолчанию.
         */
        SimpleTowerAttackVisitor() = default;

        /**
         * @brief Обрабатывает атаку простой башни.
         * @param tower Ссылка на башню, которая атакует.
         * @param dt Время, прошедшее с предыдущего обновления.
         * @return Информация об атаке.
         */
        AttackInfo visit(ITower &tower, float dt) override;

        /**
         * @brief Деструктор по умолчанию.
         */
        ~SimpleTowerAttackVisitor() override = default;
    };
}