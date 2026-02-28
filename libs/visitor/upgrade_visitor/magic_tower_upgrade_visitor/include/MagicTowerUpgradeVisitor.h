#pragma once

#include "dto.h"
#include "IUpgradeVisitor.h"

namespace TowerDefense {

    /**
     * @class MagicTowerUpgradeVisitor
     * @brief Посетитель для обработки улучшения магической башни.
     *
     * Реализует паттерн Посетитель для обработки логики улучшения магической башни.
     * Определяет, как изменяются характеристики башни при повышении уровня:
     * увеличение урона, дальности, скорости атаки.
     */
    class MagicTowerUpgradeVisitor : public IUpgradeVisitor {
    public:
        /**
         * @brief Конструктор по умолчанию.
         */
        MagicTowerUpgradeVisitor() = default;

        /**
         * @brief Применяет улучшение к магической башне.
         * @param tower Ссылка на башню, которую нужно улучшить.
         * @param levelDto DTO с параметрами нового уровня башни.
         */
        void visit(ITower &tower, LevelDTO &levelDto) override;

        /**
         * @brief Деструктор по умолчанию.
         */
        ~MagicTowerUpgradeVisitor() override = default;
    };
}