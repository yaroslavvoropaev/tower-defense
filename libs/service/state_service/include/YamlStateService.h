#pragma once

#include "IStateService.h"
#include "IMapperRepository.h"
#include "ICastleRepository.h"
#include "IEnemyRepository.h"
#include "ITowerRepository.h"
#include <yaml-cpp/yaml.h>

namespace TowerDefense {
    /**
     * @brief Конкретная реализация сервиса для управления сохранением и загрузкой состояния игры.
     *
     * YamlStateService использует формат YAML для сериализации и десериализации
     * игрового состояния. Сохраняет и загружает данные врагов, замков и башен
     * в/из YAML-файлов.
     */
    class YamlStateService final : public IStateService {
        ICastleRepository &castle_repository_; ///< Репозиторий замков
        IEnemyRepository &enemy_repository_;   ///< Репозиторий врагов
        ITowerRepository &tower_repository_;   ///< Репозиторий башен
        IMapperRepository &mapper_repository_; ///< Репозиторий мапперов

    public:
        /**
         * @brief Конструктор сервиса состояния YAML.
         *
         * @param castle_repository Репозиторий замков для сохранения/загрузки.
         * @param enemy_repository Репозиторий врагов для сохранения/загрузки.
         * @param tower_repository Репозиторий башен для сохранения/загрузки.
         * @param mapper_repository Репозиторий мапперов для преобразования объектов в DTO и обратно.
         */
        YamlStateService(ICastleRepository &castle_repository, IEnemyRepository &enemy_repository,
                         ITowerRepository &tower_repository, IMapperRepository &mapper_repository)
            : castle_repository_(castle_repository), enemy_repository_(enemy_repository),
              tower_repository_(tower_repository), mapper_repository_(mapper_repository) {}

        /**
         * @brief Загружает состояние врагов из YAML-файла.
         *
         * @param path Путь к YAML-файлу с сохраненным состоянием врагов.
         */
        void load_enemy(const std::string &path) override;

        /**
         * @brief Сохраняет состояние врагов в YAML-файл.
         *
         * @param path Путь к YAML-файлу для сохранения состояния врагов.
         */
        void save_enemy(const std::string &path) override;

        /**
         * @brief Загружает состояние замка из YAML-файла.
         *
         * @param path Путь к YAML-файлу с сохраненным состоянием замка.
         */
        void load_castle(const std::string &path) override;

        /**
         * @brief Сохраняет состояние замка в YAML-файл.
         *
         * @param path Путь к YAML-файлу для сохранения состояния замка.
         */
        void save_castle(const std::string &path) override;

        /**
         * @brief Загружает состояние башен из YAML-файла.
         *
         * @param path Путь к YAML-файлу с сохраненным состоянием башен.
         */
        void load_tower(const std::string &path) override;

        /**
         * @brief Сохраняет состояние башен в YAML-файл.
         *
         * @param path Путь к YAML-файлу для сохранения состояния башен.
         */
        void save_tower(const std::string &path) override;

        /**
         * @brief Деструктор сервиса состояния YAML.
         */
        ~YamlStateService() override = default;
    };
}