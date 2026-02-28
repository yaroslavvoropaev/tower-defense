#pragma once

#include "IEffect.h"
#include <memory>

namespace TowerDefense {
    /**
     * @brief Интерфейс фабрики для создания эффектов.
     *
     * IEffectFactory реализует паттерн "Фабричный метод" для создания объектов
     * типа IEffect. Позволяет создавать различные типы эффектов (замедление,
     * отравление, ослабление и т.д.) по их именам или типам.
     */
    class IEffectFactory {
    public:
        /**
         * @brief Возвращает имя эффекта.
         *
         * @param effect Указатель на эффект для определения имени.
         * @return std::string Имя эффекта.
         */
        virtual std::string get_effect_name(IEffect *effect) const = 0;

        /**
         * @brief Создает эффект указанного типа.
         *
         * @param type Строковый идентификатор типа эффекта.
         * @return std::unique_ptr<IEffect> Умный указатель на созданный эффект.
         */
        [[nodiscard]] virtual std::unique_ptr<IEffect> create_effect(const std::string &type) const = 0;

        /**
         * @brief Виртуальный деструктор для корректного наследования.
         */
        virtual ~IEffectFactory() = default;
    };
}