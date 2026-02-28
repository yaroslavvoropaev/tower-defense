#pragma once

#include "IEnemyRepository.h"
#include "IStrategy.h"

namespace TowerDefense {
    /**
     * @brief Конкретная реализация стратегии выбора целей "Все в радиусе".
     *
     * AllInRange возвращает всех врагов, находящихся в заданном радиусе от
     * позиции башни. Не выполняет дополнительной сортировки или фильтрации.
     */
    class AllInRange final : public IStrategy {
        IEnemyRepository &enemy_repository_; ///< Репозиторий врагов для поиска целей

    public:
        /**
         * @brief Конструктор стратегии "Все в радиусе".
         *
         * @param enemy_repository Репозиторий врагов для доступа ко всем врагам.
         */
        explicit AllInRange(IEnemyRepository &enemy_repository) : enemy_repository_(enemy_repository) {}

        /**
         * @brief Находит всех врагов в заданном радиусе от позиции.
         *
         * Использует метод get_in_range репозитория врагов для получения
         * всех целей в указанном радиусе.
         *
         * @param range Радиус поиска целей.
         * @param position Позиция, от которой ведется поиск.
         * @return std::vector<IEnemy*> Вектор указателей на всех врагов в радиусе.
         */
        std::vector<IEnemy *> find_target(float range, Point position) override;

        /**
         * @brief Деструктор стратегии.
         */
        ~AllInRange() override = default;
    };
}