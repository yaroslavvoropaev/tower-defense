#pragma once

#include "IEnemyRepository.h"
#include "IStrategy.h"

namespace TowerDefense {
    /**
     * @brief Конкретная реализация стратегии выбора целей "Ближайший к башне".
     *
     * NearestToTower выбирает врагов, находящихся в радиусе атаки башни,
     * и возвращает их.
     */
    class NearestToTower final : public IStrategy {
        IEnemyRepository &enemy_repository_; ///< Репозиторий врагов для поиска целей

    public:
        /**
         * @brief Конструктор стратегии "Ближайший к башне".
         *
         * @param enemy_repository Репозиторий врагов для доступа ко всем врагам.
         */
        explicit NearestToTower(IEnemyRepository &enemy_repository) : enemy_repository_(enemy_repository) {}

        /**
         * @brief Деструктор стратегии.
         */
        ~NearestToTower() override = default;

        /**
         * @brief Находит врагов в радиусе и сортирует их по близости к башне.
         *
         * @param radius Радиус поиска целей.
         * @param position Позиция, от которой ведется поиск (позиция башни).
         * @return std::vector<IEnemy*> Вектор указателей на врагов, отсортированных по близости к башне.
         */
        std::vector<IEnemy *> find_target(float radius, Point position) override;
    };
}