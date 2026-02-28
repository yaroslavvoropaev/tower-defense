#pragma once

#include "IStrategy.h"
#include "IEnemyRepository.h"

#include <vector>

#
namespace TowerDefense {
    /**
     * @brief Конкретная реализация стратегии выбора целей "Самый слабый".
     *
     * Weakest выбирает врагов, находящихся в радиусе атаки башни,
     * и возвращает тех, у которых наименьшее здоровье.
     */
    class Weakest final : public IStrategy {
        IEnemyRepository& enemy_repository_; ///< Репозиторий врагов для поиска целей
    public:
        /**
         * @brief Конструктор стратегии "Самый слабый".
         *
         * @param enemy_repository Репозиторий врагов для доступа ко всем врагам.
         */
        explicit Weakest(IEnemyRepository& enemy_repository) : enemy_repository_(enemy_repository) {}

        /**
         * @brief Находит врагов в радиусе и выбирает самых слабых.
         *
         * @param radius Радиус поиска целей.
         * @param position Позиция, от которой ведется поиск (позиция башни).
         * @return std::vector<IEnemy*> Вектор указателей на врагов, отсортированных по слабости.
         */
        std::vector<IEnemy *> find_target(float radius, Point position) override;

        /**
         * @brief Деструктор стратегии.
         */
        ~Weakest() override = default;
    };
}