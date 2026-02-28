#pragma once

namespace TowerDefense {
    /**
     * @brief Интерфейс для объектов, наносящих урон.
     *
     * IDamageable определяет интерфейс для объектов, которые могут наносить
     * урон другим объектам.
     */
    class IDamageable {
    public:
        virtual ~IDamageable() = default;

        /**
         * @brief Возвращает количество урона, наносимого объектом.
         * @return Величина урона.
         */
        [[nodiscard]] virtual float get_damage() const = 0;

        /**
         * @brief Устанавливает количество урона, наносимого объектом.
         * @param damage Новая величина урона.
         */
        virtual void set_damage(float damage) = 0;
    };

    /**
     * @brief Конкретный класс, представляющий башню с уроном.
     *
     * DamageTower реализует интерфейс IDamageable и хранит значение урона.
     * Может быть унаследован конкретными типами уронных башен.
     */
    class DamageTower : public IDamageable {
        float damage_;  ///< Величина урона, наносимого башней

    public:
        /**
         * @brief Конструктор башни с уроном.
         *
         * @param damage Начальное значение урона.
         */
        explicit DamageTower(float damage) : damage_(damage) {}

        /**
         * @brief Возвращает текущий урон башни.
         * @return Величина урона.
         */
        [[nodiscard]] float get_damage() const override;

        /**
         * @brief Устанавливает урон башни.
         * @param damage Новая величина урона.
         */
        void set_damage(float damage) override;

        ~DamageTower() override = default;
    };
}