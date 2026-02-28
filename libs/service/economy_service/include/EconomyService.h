#pragma once

#include "IEconomyService.h"
#include "dto.h"

#include <typeindex>

#include "SimpleTower.h"
#include "MagicTower.h"
#include "MagicTrap.h"
#include "ICastleRepository.h"
#include "ITowerRepository.h"
#include "IUpgradeVisitor.h"

namespace TowerDefense {
    /**
     * @brief Конкретная реализация сервиса для управления экономикой и улучшениями.
     *
     * EconomyService отвечает за обработку улучшений башен, проверку возможности
     * апгрейда и применение улучшений через паттерн "Посетитель".
     */
    class EconomyService final : public IEconomyService {
        ITowerRepository &tower_repository_;   ///< Репозиторий башен
        ICastleRepository &castle_repository_; ///< Репозиторий замков
        std::unordered_map<std::type_index, std::vector<LevelDTO>> level_up_map_; ///< Карта уровней улучшений по типам башен
        std::unordered_map<std::type_index, std::unique_ptr<IUpgradeVisitor>> visitors_; ///< Посетители улучшений по типам башен

    public:
        /**
         * @brief Конструктор сервиса экономики.
         *
         * Инициализирует сервис с конфигурацией уровней улучшений для различных типов башен.
         *
         * @param tower_repository Репозиторий башен для доступа к объектам башен.
         * @param castle_repository Репозиторий замков для проверки и списания золота.
         * @param config Конфигурация уровней улучшений из файла конфигурации.
         */
        EconomyService(ITowerRepository &tower_repository, ICastleRepository &castle_repository,
                       const LevelConfig &config)
            : tower_repository_(tower_repository), castle_repository_(castle_repository) {
            level_up_map_.emplace(typeid(SimpleTower), config.levels.at("simple_tower"));
            level_up_map_.emplace(typeid(MagicTower), config.levels.at("magic_tower"));
            level_up_map_.emplace(typeid(MagicTrap), config.levels.at("magic_trap"));
        }

        /**
         * @brief Регистрирует посетителя улучшений для определенного типа объекта.
         *
         * @param type_index Индекс типа объекта, для которого регистрируется посетитель.
         * @param visitor Умный указатель на объект посетителя улучшений.
         */
        void add_visitor(std::type_index type_index, std::unique_ptr<IUpgradeVisitor> visitor) override;

        /**
         * @brief Выполняет улучшение объекта по его идентификатору.\
         *
         * @param id Идентификатор башни для улучшения.
         * @return bool true, если улучшение успешно выполнено; false, если улучшение
         *         невозможно (недостаточно золота, максимальный уровень и т.д.).
         */
        bool upgrade(ID id) override;

        /**
         * @brief Деструктор сервиса экономики.
         */
        ~EconomyService() override = default;
    };
}