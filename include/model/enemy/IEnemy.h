#pragma once

#include "IEffectable.h"
#include "IHealthable.h"
#include "IMoveable.h"
#include "id.h"

namespace TowerDefense {
    /**
     * @brief Интерфейс, представляющий врага в игре Tower Defense.
     *
     * IEnemy объединяет функциональность перемещения (IMoveable),
     * применения эффектов (IEffectable) и управления здоровьем (IHealthable).
     * Определяет поведение вражеских юнитов, их характеристики и возможность клонирования.
     */
    class IEnemy : public IMoveable, public IEffectable, public IHealthable {
    public:
        ~IEnemy() override = default;

        /**
         * @brief Возвращает имя типа врага.
         * @return Имя врага.
         */
        [[nodiscard]] virtual std::string get_name() const = 0;

        /**
         * @brief Возвращает количество золота, которое дается за убийство врага.
         * @return Количество золота за убийство.
         */
        [[nodiscard]] virtual size_t get_gold() const = 0;

        /**
         * @brief Возвращает уникальный идентификатор врага.
         * @return Идентификатор врага.
         */
        [[nodiscard]] virtual ID get_ID() const = 0;

        /**
         * @brief Устанавливает уникальный идентификатор врага.
         * @param id Новый идентификатор.
         */
        virtual void set_ID(ID id) = 0;

        /**
         * @brief Создает глубокую копию врага.
         *
         * Реализует паттерн "Прототип", позволяя создавать идентичные копии
         * врагов для спавна волн или других игровых механик.
         *
         * @return std::unique_ptr<IEnemy> Умный указатель на копию врага.
         */
        virtual std::unique_ptr<IEnemy> clone() = 0;
    };
}