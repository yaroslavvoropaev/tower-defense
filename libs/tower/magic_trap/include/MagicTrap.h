#pragma once

#include "AbstractTower.h"
#include "EffectTower.h"

namespace TowerDefense {

    /**
     * @class MagicTrap
     * @brief Магическая ловушка, применяющая эффекты без нанесения урона.
     *
     * Класс представляет собой магическую ловушку, которая применяет эффекты
     * к врагам, но не наносит прямого урона. Наследуется от AbstractTower
     * и EffectTower. Является конечным (final) классом.
     */
    class MagicTrap final : public AbstractTower, public EffectTower {
    public:
        /**
         * @brief Конструктор магической ловушки.
         * @param id Уникальный идентификатор ловушки.
         * @param range Дальность действия ловушки.
         * @param level Уровень ловушки.
         * @param position Позиция ловушки на карте.
         * @param strategy Указатель на стратегию выбора цели.
         * @param rate_of_fire Скорость активации (раз в секунду).
         * @param effect Уникальный указатель на эффект, применяемый ловушкой.
         */
        MagicTrap(ID id, float range, size_t level, Point position, IStrategy *strategy,
                  float rate_of_fire, std::unique_ptr<IEffect> effect) :
            AbstractTower(id, range, level, position, strategy, rate_of_fire),
            EffectTower(std::move(effect)) {}

        /**
         * @brief Деструктор по умолчанию.
         */
        ~MagicTrap() override = default;

        /**
         * @brief Создает глубокую копию текущей ловушки.
         * @return Указатель на копию ловушки.
         */
        std::unique_ptr<ITower> clone() override;
    };
}