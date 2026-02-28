#pragma once
#include <atomic>

namespace TowerDefense {
    /**
     * @brief Модуль управления здоровьем для игровых объектов.
     *
     * HealthModule отвечает за хранение и изменение здоровья объекта,
     * учет уязвимостей и нанесение урона. Использует атомарные операции
     * для потокобезопасности.
     */
    class HealthModule {
        std::atomic<float> health_;      ///< Текущее здоровье объекта
        float max_health_{};               ///< Максимальное здоровье объекта
        std::atomic<int> weaknessC_ {};  ///< Величина ослабления (в процентах)

    public:
        /**
         * @brief Конструктор модуля здоровья.
         *
         * @param health Начальное здоровье объекта.
         * @param max_health Максимальное здоровье объекта.
         */
        explicit HealthModule(float health, float max_health) : health_(health), max_health_(max_health) {}
        /**
         * brief Конструктор по умолчанию.
         */
        HealthModule() = default;
        /**
         * @brief Возвращает текущее здоровье объекта.
         * @return Текущее значение здоровья.
         */
        [[nodiscard]] float get_current_health() const;

        /**
         * @brief Наносит урон объекту с учетом уязвимостей.
         *
         * @param damage Базовый урон до применения модификаторов.
         */
        void take_damage(float damage);

        /**
         * @brief Изменяет уровень уязвимости объекта.
         *
         * @param weakness Изменение уязвимости (может быть положительным или отрицательным).
         */
        void change_weakness(int weakness);

        /**
         * @brief Возвращает максимальное здоровье объекта.
         * @return Максимальное значение здоровья.
         */
        [[nodiscard]] float get_max_health() const;
    };
}