#pragma once

#include "IEnemyRepository.h"
#include "ICastleRepository.h"

#include "IEnemyService.h"

namespace TowerDefense {
    /**
     * @brief Конкретная реализация сервиса для управления атаками врагов.
     *
     * EnemyService обрабатывает логику атак всех врагов на игровом поле.
     * Проверяет расстояние до замка и наносит урон при достижении врагом замка.
     */
    class EnemyService final : public IEnemyService {
        ICastleRepository &castle_repository_; ///< Репозиторий замков
        IEnemyRepository &enemy_repository_;   ///< Репозиторий врагов
    public:
        /**
         * @brief Конструктор сервиса врагов.
         *
         * @param castle_repository Репозиторий замков для доступа к объекту замка.
         * @param enemy_repository Репозиторий врагов для доступа ко всем врагам.
         */
        EnemyService(ICastleRepository &castle_repository, IEnemyRepository &enemy_repository)
            : castle_repository_(castle_repository), enemy_repository_(enemy_repository) {}

        /**
         * @brief Выполняет атаку всех врагов на игровом поле.
         *
         */
        void attack_all() override;

        /**
         * @brief Деструктор сервиса врагов.
         */
        ~EnemyService() override = default;
    };
}