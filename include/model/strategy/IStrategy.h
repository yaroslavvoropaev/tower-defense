#pragma once

#include "IEnemy.h"
#include <vector>

namespace TowerDefense {
    /**
     * @brief Интерфейс стратегии для выбора целей атаки.
     *
     * IStrategy определяет интерфейс для различных алгоритмов выбора целей
     * атаки. Реализации стратегий могут выбирать цели по разным критериям:
     * ближайшая цель, цель с наибольшим здоровьем, и т.д.
     */
    class IStrategy {
    public:
        /**
         * @brief Находит цели для атаки в заданном радиусе.
         *
         * @param range Радиус поиска целей.
         * @param position Позиция, от которой ведется поиск.
         * @return std::vector<IEnemy*> Вектор указателей на найденные цели.
         */
        virtual std::vector<IEnemy *> find_target(float range, Point position) = 0;

        /**
         * @brief Виртуальный деструктор для обеспечения корректного наследования.
         */
        virtual ~IStrategy() = default;
    };
}