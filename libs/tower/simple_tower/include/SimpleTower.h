#pragma once

#include "AbstractTower.h"
#include "DamageTower.h"
#include "IStrategy.h"
#include "id.h"

namespace TowerDefense {

    /**
     * @class SimpleTower
     * @brief Простая башня, наносящая только урон без эффектов.
     *
     * Класс представляет собой простую башню, которая наносит урон врагам,
     * но не применяет дополнительных эффектов. Наследуется от AbstractTower
     * и DamageTower. Является конечным (final) классом.
     */
    class SimpleTower final : public AbstractTower, public DamageTower {
    public:
        /**
         * @brief Конструктор простой башни.
         * @param id Уникальный идентификатор башни.
         * @param range Дальность атаки башни.
         * @param level Уровень башни.
         * @param position Позиция башни на карте.
         * @param strategy Указатель на стратегию выбора цели.
         * @param damage Урон, наносимый башней.
         * @param rate_of_fire Скорость атаки (выстрелов в секунду).
         */
        SimpleTower(ID id, float range, size_t level, Point position, IStrategy *strategy,
                    float damage, float rate_of_fire) :
            AbstractTower(id, range, level, position, strategy, rate_of_fire),
            DamageTower(damage) {}

        /**
         * @brief Создает глубокую копию текущей башни.
         * @return Указатель на копию башни.
         */
        std::unique_ptr<ITower> clone() override;

        /**
         * @brief Деструктор по умолчанию.
         */
        ~SimpleTower() override = default;
    };
}