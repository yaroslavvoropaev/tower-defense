#pragma once

#include "AbstractTower.h"
#include "IAttackVisitor.h"

namespace TowerDefense {
    /**
     * @class MagicTowerAttackVisitor
     * @brief Посетитель для обработки атаки магической башни.
     *
     * Реализует паттерн Посетитель для обработки логики атаки магической башни.
     * Определяет, как магическая башня взаимодействует с целями, включая
     * нанесение урона и применение эффектов.
     */
    class MagicTowerAttackVisitor : public IAttackVisitor {
    public:
        /**
         * @brief Конструктор по умолчанию.
         */
        MagicTowerAttackVisitor() = default;

        /**
         * @brief Обрабатывает атаку магической башни.
         * @param tower Ссылка на башню, которая атакует.
         * @param dt Время, прошедшее с предыдущего обновления.
         * @return Информация об атаке.
         */
        AttackInfo visit(ITower &tower, float dt) override;

        /**
         * @brief Деструктор по умолчанию.
         */
        ~MagicTowerAttackVisitor() override = default;
    };
}