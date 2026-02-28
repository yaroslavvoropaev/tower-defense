#pragma once

#include "dto.h"
#include "IUpgradeVisitor.h"

namespace TowerDefense {

    /**
     * @class SimpleTowerUpgradeVisitor
     * @brief Посетитель для обработки улучшения простой башни.
     *
     * Реализует паттерн Посетитель для обработки логики улучшения простой башни.
     * Определяет, как изменяются характеристики башни при повышении уровня:
     * увеличение урона, дальности и скорости атаки.
     */
    class SimpleTowerUpgradeVisitor : public IUpgradeVisitor {
    public:
        /**
         * @brief Конструктор по умолчанию.
         */
        SimpleTowerUpgradeVisitor() = default;

        /**
         * @brief Применяет улучшение к простой башне.
         * @param tower Ссылка на башню, которую нужно улучшить.
         * @param levelDto DTO с параметрами нового уровня башни.
         */
        void visit(ITower &tower, LevelDTO &levelDto) override;

        /**
         * @brief Деструктор по умолчанию.
         */
        ~SimpleTowerUpgradeVisitor() override = default;
    };
}