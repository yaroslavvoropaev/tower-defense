#pragma once

#include "IEffect.h"

namespace TowerDefense {
    /**
     * @brief Интерфейс для объектов, которые могут применять эффекты.
     *
     * IEffectHaveable определяет интерфейс для объектов, которые могут
     * накладывать эффекты на врагов.
     * Используется для магических башен и других объектов с особыми эффектами.
     */
    class IEffectHaveable {
    public:
        virtual ~IEffectHaveable() = default;

        /**
         * @brief Возвращает эффект, применяемый объектом.
         *
         * @return std::unique_ptr<IEffect> Умный указатель на копию эффекта.
         */
        [[nodiscard]] virtual std::unique_ptr<IEffect> get_effect() const = 0;
    };

    /**
     * @brief Конкретный класс, представляющий башню с эффектами.
     *
     * EffectTower реализует интерфейс IEffectHaveable и хранит эффект,
     * который может быть применен к врагам. Может быть унаследован
     * конкретными типами магических башен.
     */
    class EffectTower : public IEffectHaveable {
        std::unique_ptr<IEffect> effect_;  ///< Эффект, применяемый башней

    public:
        /**
         * @brief Конструктор башни с эффектом.
         *
         * @param effect Умный указатель на эффект для применения.
         *              Владение эффектом передается башне.
         */
        explicit EffectTower(std::unique_ptr<IEffect> effect) : effect_(std::move(effect)) {}

        /**
         * @brief Возвращает копию эффекта башни.
         *
         * @return std::unique_ptr<IEffect> Умный указатель на копию эффекта.
         */
        [[nodiscard]] std::unique_ptr<IEffect> get_effect() const override;

        ~EffectTower() override = default;
    };
}