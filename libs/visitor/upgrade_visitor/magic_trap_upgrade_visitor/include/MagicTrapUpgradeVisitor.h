#pragma once

#include "dto.h"
#include "IUpgradeVisitor.h"

namespace TowerDefense {

    /**
     * @class MagicTrapUpgradeVisitor
     * @brief Посетитель для обработки улучшения магической ловушки.
     *
     * Реализует паттерн Посетитель для обработки логики улучшения магической ловушки.
     * Определяет, как изменяются характеристики ловушки при повышении уровня:
     * увеличение дальности, скорости активации и мощности эффектов.
     */
    class MagicTrapUpgradeVisitor : public IUpgradeVisitor {
    public:
        /**
         * @brief Конструктор по умолчанию.
         */
        MagicTrapUpgradeVisitor() = default;

        /**
         * @brief Применяет улучшение к магической ловушке.
         * @param tower Ссылка на ловушку, которую нужно улучшить.
         * @param levelDto DTO с параметрами нового уровня ловушки.
         */
        void visit(ITower &tower, LevelDTO &levelDto) override;

        /**
         * @brief Деструктор по умолчанию.
         */
        ~MagicTrapUpgradeVisitor() override = default;
    };
}