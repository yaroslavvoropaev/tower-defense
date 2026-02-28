#pragma once

#include "IStrategy.h"
#include "IEnemyRepository.h"
#include "ICastleRepository.h"

namespace TowerDefense {
    /**
     * @brief Конкретная реализация стратегии выбора целей "Ближайший к замку".
     *
     * NearestToCastle выбирает врагов, находящихся в радиусе атаки башни,
     * и возвращает тех, которые ближе всего к замку.
     */
    class NearestToCastle final : public IStrategy {
        IEnemyRepository &enemy_repository_; ///< Репозиторий врагов для поиска целей
        ICastleRepository &castle_repository_; ///< Репозиторий замков для получения позиции замка

    public:
        /**
         * @brief Конструктор стратегии "Ближайший к замку".
         *
         * @param enemy_repository Репозиторий врагов для доступа ко всем врагам.
         * @param castle_repository Репозиторий замков для получения позиции замка.
         */
        NearestToCastle(IEnemyRepository &enemy_repository, ICastleRepository &castle_repository)
            : enemy_repository_(enemy_repository), castle_repository_(castle_repository) {}

        /**
         * @brief Деструктор стратегии.
         */
        ~NearestToCastle() override = default;

        /**
         * @brief Находит врагов в радиусе и выбирает ближайших к замку.
         *
         * @param range Радиус поиска целей.
         * @param position Позиция, от которой ведется поиск (позиция башни).
         * @return std::vector<IEnemy*> Вектор указателей на врагов, отсортированных по близости к замку.
         */
        std::vector<IEnemy *> find_target(float range, Point position) override;
    };
}