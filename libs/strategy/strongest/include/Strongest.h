#pragma once

#include "IStrategy.h"
#include "IEnemyRepository.h"

namespace TowerDefense {
    /**
     * @brief Конкретная реализация стратегии выбора целей "Самый сильный".
     *
     * Strongest выбирает врагов, находящихся в радиусе атаки башни,
     * и возвращает тех, у которых наибольшее здоровье.
     */
    class Strongest final : public IStrategy {
        IEnemyRepository &enemy_repository_; ///< Репозиторий врагов для поиска целей

    public:
        /**
         * @brief Конструктор стратегии "Самый сильный".
         *
         * @param enemy_repository Репозиторий врагов для доступа ко всем врагам.
         */
        explicit Strongest(IEnemyRepository &enemy_repository) : enemy_repository_(enemy_repository) {}

        /**
         * @brief Деструктор стратегии.
         */
        ~Strongest() override = default;

        /**
         * @brief Находит врагов в радиусе и выбирает самых сильных.
         *
         * @param radius Радиус поиска целей.
         * @param position Позиция, от которой ведется поиск.
         * @return std::vector<IEnemy*> Вектор указателей на врагов, отсортированных по силе.
         */
        std::vector<IEnemy *> find_target(float radius, Point position) override;
    };
}