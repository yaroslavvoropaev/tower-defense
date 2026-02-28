#pragma once

#include "AbstractTower.h"
#include "DamageTower.h"
#include "EffectTower.h"

namespace TowerDefense {

    /**
     * @class MagicTower
     * @brief Магическая башня, наносящая урон и применяющая эффекты.
     *
     * Класс представляет собой магическую башню, которая объединяет функциональность
     * нанесения урона (через DamageTower) и применения специальных эффектов
     * (через EffectTower). Наследуется от AbstractTower, DamageTower и EffectTower.
     * Является конечным (final) классом.
     */
    class MagicTower final : public AbstractTower, public DamageTower, public EffectTower {
    public:
        /**
         * @brief Конструктор магической башни.
         * @param id Уникальный идентификатор башни.
         * @param range Дальность атаки башни.
         * @param level Уровень башни.
         * @param position Позиция башни на карте.
         * @param strategy Указатель на стратегию выбора цели.
         * @param damage Урон, наносимый башней.
         * @param rate_of_fire Скорость атаки (выстрелов в секунду).
         * @param effect Уникальный указатель на эффект, применяемый башней.
         */
        MagicTower(ID id, float range, size_t level, Point position, IStrategy *strategy, float damage, float rate_of_fire, std::unique_ptr<IEffect> effect) :
            AbstractTower(id, range, level, position, strategy, rate_of_fire), DamageTower(damage), EffectTower(std::move(effect)) {}
        
        /**
         * @brief Деструктор по умолчанию.
         */
        ~MagicTower() override = default;

        /**
         * @brief Создает глубокую копию текущей башни.
         * @return Указатель на копию башни.
         */
        std::unique_ptr<ITower> clone() override;
    };

}