#pragma once

#include "dto.h"
#include "SlowEffect.h"
#include "PoisonEffect.h"
#include "WeaknessEffect.h"

#include <unordered_map>
#include <string>
#include <typeindex>

#include "IEffectFactory.h"

namespace TowerDefense {
    /**
     * @brief Конкретная реализация фабрики для создания эффектов.
     *
     * EffectFactory создает различные типы эффектов
     * на основе конфигурации и предоставляет доступ по имени типа.
     */
    class EffectFactory final : public IEffectFactory {
        std::unordered_map<std::string, std::unique_ptr<IEffect>> effects_; ///< Карта эффектов по имя-тип
        std::unordered_map<std::type_index, std::string> effect_types_; ///< Карта соответствий тип-имя
    public:
        /**
         * @brief Конструктор фабрики эффектов.
         *
         * Инициализирует фабрику на основе конфигурации, создавая прототипы
         * эффектов для каждого типа, определенного в конфигурации.
         *
         * @param config Конфигурация эффектов из файла конфигурации.
         */
        EffectFactory(const EffectConfig& config) {
            for (auto &dto : config.effects) {
                if (dto.type == "slow") {
                    effects_.emplace(dto.type, std::make_unique<SlowEffect>(dto.duration, dto.duration));
                } else if (dto.type == "poison") {
                    effects_.emplace(dto.type, std::make_unique<PoisonEffect>(dto.magnitude, dto.duration));
                } else if (dto.type == "weakness") {
                    effects_.emplace(dto.type, std::make_unique<WeaknessEffect>(dto.magnitude, dto.duration));
                }
            }
            effect_types_.emplace(typeid(SlowEffect), "slow");
            effect_types_.emplace(typeid(WeaknessEffect), "weakness");
            effect_types_.emplace(typeid(PoisonEffect), "poison");
        }

        /**
         * @brief Создает эффект указанного типа.
         *
         * @param type Строковый идентификатор типа эффекта ("slow", "poison", "weakness").
         * @return std::unique_ptr<IEffect> Умный указатель на созданный эффект.
         * @throw std::out_of_range выбрасывать исключение, если тип эффекта неизвестен.
         */
        std::unique_ptr<IEffect> create_effect(const std::string &type) const override;

        /**
         * @brief Возвращает имя эффекта по объекту.
         *
         * @param effect Указатель на объект эффекта.
         * @return std::string Имя типа эффекта.
         * @throw std::out_of_range выбрасывать исключение, если тип эффекта неизвестен.
         */
        std::string get_effect_name(IEffect *effect) const override;
        /**
         * @brief Деструктор фабрики эффектов.
         */
        ~EffectFactory() override = default;
    };
}