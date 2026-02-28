#pragma once

#include "IEffect.h"
#include <vector>
#include <mutex>

namespace TowerDefense {
    /**
     * @brief Модуль управления эффектами для игровых объектов.
     *
     * EffectModule отвечает за хранение, обновление и удаление эффектов,
     * примененных к объекту (например, врагу). Обеспечивает потокобезопасность
     * при добавлении эффектов с использованием мьютекса.
     */
    class EffectModule {
        std::vector<std::unique_ptr<IEffect>> effects_; ///< Вектор активных эффектов
        mutable std::mutex mutex_; ///< Мьютекс для потокобезопасных операций

    public:
        EffectModule() = default;

        /**
         * @brief Добавляет новый эффект к объекту.
         *
         * @param enemy Ссылка на врага, к которому применяется эффект.
         * @param effect Умный указатель на эффект для добавления.
         *              Владение эффектом передается модулю.
         */
        void add_effect(IEnemy &enemy, std::unique_ptr<IEffect> effect);

        /**
         * @brief Обновляет все активные эффекты.
         *
         * @param enemy Ссылка на врага, на которого действуют эффекты.
         * @param dt Время, прошедшее с предыдущего обновления (в секундах).
         */
        void all_update(IEnemy &enemy, float dt);
    };
}