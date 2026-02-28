#pragma once

#include <typeindex>
#include <future>
#include <unordered_map>
#include "IAttackVisitor.h"
#include "IEnemyRepository.h"
#include "ITowerRepository.h"
#include "ICastleRepository.h"
#include "ITowerService.h"
#include "MagicTower.h"

namespace TowerDefense{
    /**
     * @class TowerService
     * @brief Сервис для управления атаками башен.
     *
     * Реализует логику атаки всех башен по врагам, поддерживает как последовательное,
     * так и параллельное выполнение. Использует паттерн Посетитель для обработки
     * различных типов башен.
     */
    class TowerService final : public ITowerService {
        ITowerRepository &tower_repository_;           ///< Репозиторий для доступа к данным башен
        IEnemyRepository &enemy_repository_;           ///< Репозиторий для доступа к данным врагов
        ICastleRepository &castle_repository_;         ///< Репозиторий для доступа к данным замка
        std::unordered_map<std::type_index, std::unique_ptr<IAttackVisitor>> visitors_; ///< Посетители для различных типов башен
        size_t num_threads_ = std::thread::hardware_concurrency(); ///< Количество потоков для параллельных вычислений

    public:
        /**
         * @brief Конструктор сервиса башен.
         * @param tower_repository   Репозиторий башен
         * @param enemy_repository   Репозиторий врагов
         * @param castle_repository  Репозиторий замка
         */
        TowerService(ITowerRepository &tower_repository,
                     IEnemyRepository &enemy_repository,
                     ICastleRepository &castle_repository) :
            tower_repository_(tower_repository),
            enemy_repository_(enemy_repository),
            castle_repository_(castle_repository) {}

        /**
         * @brief Добавляет посетителя для обработки атак определенного типа башен.
         * @param type_index  Тип башни
         * @param visitor     Уникальный указатель на посетителя
         */
        void add_visitor(std::type_index type_index, std::unique_ptr<IAttackVisitor> visitor) override;

        /**
         * @brief Выполняет атаку всех башен последовательно.
         * @param dt  Время, прошедшее с предыдущего обновления
         * @return   Вектор информации об атаках (какая башня кого атаковала и.т.д.)
         */
        std::vector<AttackInfo> attack_all(float dt) override;

        /**
         * @brief Выполняет атаку всех башен параллельно.
         * @param dt  Время, прошедшее с предыдущего обновления
         * @return   Вектор информации об атаках (какая башня кого атаковала и.т.д.)
         */
        std::vector<AttackInfo> attack_all_par(float dt) override;

        ~TowerService() override = default;
    };
}