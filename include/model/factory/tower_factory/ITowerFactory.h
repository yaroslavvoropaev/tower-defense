#pragma once

#include "AbstractTower.h"
#include <memory>

namespace TowerDefense {
    /**
     * @brief Интерфейс фабрики для создания башен.
     *
     * ITowerFactory реализует паттерн "Фабричный метод" для создания объектов
     * типа ITower. Позволяет создавать различные типы башен с заданными
     * характеристиками и начальной позицией.
     */
    class ITowerFactory {
    public:
        /**
         * @brief Создает башню указанного типа в заданной позиции.
         *
         * @param type Строковый идентификатор типа башни.
         * @param coord Начальная позиция башни на игровом поле.
         * @return std::unique_ptr<ITower> Умный указатель на созданную башню.
         */
        [[nodiscard]] virtual std::unique_ptr<ITower> create_tower(const std::string &type, const Point &coord) const = 0;

        /**
         * @brief Виртуальный деструктор для корректного наследования.
         */
        virtual ~ITowerFactory() = default;
    };
}