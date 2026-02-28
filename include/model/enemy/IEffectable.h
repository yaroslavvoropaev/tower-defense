#pragma once

#include <memory>

namespace TowerDefense {
    class IEffect;

    /**
     * @brief Интерфейс для объектов, которые могут получать эффекты.
     *
     * IEffectable определяет интерфейс для игровых объектов, которые могут
     * подвергаться воздействию эффектов (например, замедление, отравление).
     * Позволяет добавлять и управлять активными эффектами на объекте.
     */
    class IEffectable {
    public:
        virtual ~IEffectable() = default;

        /**
         * @brief Добавляет эффект к объекту.
         *
         * @param effect Умный указатель на эффект для добавления.
         *              Владение эффектом передается объекту.
         */
        virtual void add_effect(std::unique_ptr<IEffect> effect) = 0;
    };
}