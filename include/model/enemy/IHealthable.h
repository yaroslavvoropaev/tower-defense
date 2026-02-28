#pragma once

namespace TowerDefense {
    /**
     * @brief Интерфейс для объектов, имеющих здоровье.
     *
     * IHealthable определяет базовую функциональность для управления здоровьем
     * игровых объектов. Включает получение урона, отслеживание текущего и
     * максимального здоровья, а также обновление состояния.
     */
    class IHealthable {
    public:
        virtual ~IHealthable() = default;

        /**
         * @brief Возвращает максимальное здоровье объекта.
         * @return Максимальное значение здоровья.
         */
        [[nodiscard]] virtual float get_max_health() const = 0;

        /**
         * @brief Возвращает текущее здоровье объекта.
         * @return Текущее значение здоровья.
         */
        [[nodiscard]] virtual float get_health() const = 0;

        /**
         * @brief Наносит урон объекту.
         * @param damage Величина наносимого урона.
         */
        virtual void take_damage(float damage) = 0;

        /**
         * @brief Изменяет ослабление объекта к определенным типам урона.
         * @param weakness_value величина ослабления.
         */
        virtual void change_weakness(int weakness_value) = 0;

        /**
         * @brief Обновляет состояние объекта (например, регенерация здоровья).
         * @param delta_time Время, прошедшее с предыдущего обновления.
         */
        virtual void update(float delta_time) = 0;
    };
}