#pragma once

#include <atomic>

#include "ICastle.h"

#include <string>

namespace TowerDefense {
    /**
     * @brief Конкретная реализация замка в игре Tower Defense.
     *
     * Класс Castle является финальной реализацией интерфейса ICastle.
     * Содержит модули для управления здоровьем, экономикой, именем,
     * позицией и идентификатором замка.
     */
    class Castle final : public ICastle {
        ID id_;                      ///< Уникальный идентификатор замка
        std::string name_;           ///< Имя замка
        float health_;               ///< Текущее здоровье замка
        float max_health_;           ///< Максимальное здоровье замка
        size_t gold_;                ///< Количество золота у замка
        Point position_;             ///< Позиция замка на игровом поле

    public:
        /**
         * @brief Конструктор замка.
         *
         * @param id Уникальный идентификатор замка.
         * @param name Имя замка.
         * @param health Начальное здоровье замка.
         * @param max_health Максимальное здоровье замка.
         * @param amount_gold Начальное количество золота.
         * @param position Позиция замка на карте.
         */
        Castle(ID id, const std::string &name, float health, float max_health,
               size_t amount_gold, Point position)
            : id_(id), name_(name), health_(health), max_health_(max_health),
              gold_(amount_gold), position_(position) {}


        /**
         * @brief Возвращает текущее здоровье замка.
         *
         * @return float Текущее значение здоровья.
         */
        [[nodiscard]] float get_health() const override;

        /**
         * @brief Возвращает максимальное здоровье замка.
         *
         * @return float Максимальное значение здоровья.
         */
        [[nodiscard]] float get_max_health() const override;

        /**
         * @brief Устанавливает здоровье замка.
         *
         * @param health Новое значение здоровья.
         * @note Значение будет ограничено диапазоном [0, max_health_].
         */
        void set_health(float health) override;

        /**
         * @brief Наносит урон замку.
         *
         * Уменьшает текущее здоровье на указанное значение.
         *
         * @param damage Величина наносимого урона.
         * @note Здоровье не может стать отрицательным.
         */
        void take_damage(float damage) override;


        /**
         * @brief Возвращает текущее количество золота у замка.
         *
         * @return size_t Количество золота.
         */
        [[nodiscard]] size_t get_gold() const override;

        /**
         * @brief Добавляет золото в казну замка.
         *
         * @param amount Количество добавляемого золота.
         */
        void add_gold(size_t amount) override;

        /**
         * @brief Вычитает золото из казны замка.
         *
         * @param amount Количество вычитаемого золота.
         * @note Количество золота не может стать отрицательным.
         *       Если amount превышает текущее количество золота,
         *       значение будет установлено в 0.
         */
        void subtract_gold(size_t amount) override;


        /**
         * @brief Возвращает имя замка.
         *
         * @return std::string Имя замка.
         */
        [[nodiscard]] std::string get_name() const override;


        /**
         * @brief Возвращает позицию замка на игровом поле.
         *
         * @return Point Координаты позиции замка.
         */
        [[nodiscard]] Point get_position() const override;


        /**
         * @brief Возвращает уникальный идентификатор замка.
         *
         * @return ID Идентификатор замка.
         */
        [[nodiscard]] ID get_ID() const override;

        /**
         * @brief Устанавливает уникальный идентификатор замка.
         *
         * @param id Новый идентификатор.
         */
        void set_ID(ID id) override;


        /**
         * @brief Деструктор замка.
         */
        ~Castle() override = default;
    };
}