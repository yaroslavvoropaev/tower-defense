#pragma once

#include <typeindex>

#include "IMapperRepository.h"

#include "SimpleTower.h"

namespace TowerDefense {
    /**
     * @brief Конкретная реализация репозитория для управления мапперами.
     *
     * MapperRepository хранит различные типы мапперов для преобразования
     * между объектами домена и DTO. Поддерживает мапперы для врагов, замков
     * и различных типов башен.
     */
    class MapperRepository final : public IMapperRepository {
        std::unique_ptr<IEnemyMapper> from_enemy_dto_; ///< Маппер для создания врагов из DTO
        std::unique_ptr<IEnemyDTOMapper> from_enemy_; ///< Маппер для преобразования врагов в DTO
        std::unique_ptr<ICastleMapper> from_castle_dto_; ///< Маппер для создания замков из DTO
        std::unique_ptr<ICastleDTOMapper> from_castle_; ///< Маппер для преобразования замков в DTO
        std::unordered_map<std::string, std::unique_ptr<ITowerMapper>> from_tower_dto_; ///< Мапперы для создания башен из DTO
        std::unordered_map<std::type_index, std::unique_ptr<ITowerDTOMapper>> from_tower_; ///< Мапперы для преобразования башен в DTO

    public:
        /**
         * @brief Конструктор репозитория мапперов.
         */
        MapperRepository() = default;

        /**
         * @brief Регистрирует маппер для создания врагов из DTO.
         *
         * @param mapper Умный указатель на маппер врагов.
         */
        void add_enemy_mapper(std::unique_ptr<IEnemyMapper> mapper) override;

        /**
         * @brief Регистрирует маппер для преобразования врагов в DTO.
         *
         * @param mapper Умный указатель на DTO-маппер врагов.
         */
        void add_enemy_dto_mapper(std::unique_ptr<IEnemyDTOMapper> mapper) override;

        /**
         * @brief Регистрирует маппер для создания замков из DTO.
         *
         * @param mapper Умный указатель на маппер замков.
         */
        void add_castle_mapper(std::unique_ptr<ICastleMapper> mapper) override;

        /**
         * @brief Регистрирует маппер для преобразования замков в DTO.
         *
         * @param mapper Умный указатель на DTO-маппер замков.
         */
        void add_castle_dto_mapper(std::unique_ptr<ICastleDTOMapper> mapper) override;

        /**
         * @brief Регистрирует маппер для создания башен из DTO.
         *
         * @param type_name Имя типа башни.
         * @param mapper Умный указатель на маппер башен.
         */
        void add_tower_mapper(std::string type_name, std::unique_ptr<ITowerMapper> mapper) override;

        /**
         * @brief Регистрирует маппер для преобразования башен в DTO.
         *
         * @param type_index Индекс типа башни.
         * @param mapper Умный указатель на DTO-маппер башен.
         */
        void add_tower_dto_mapper(std::type_index type_index, std::unique_ptr<ITowerDTOMapper> mapper) override;

        /**
         * @brief Преобразует DTO башни в объект башни.
         *
         * @param dto Объект DTO башни.
         * @return std::unique_ptr<ITower> Умный указатель на созданную башню.
         */
        std::unique_ptr<ITower> dto_to_tower(const TowerDTO &dto) override;

        /**
         * @brief Преобразует объект башни в DTO.
         *
         * @param tower Указатель на объект башни.
         * @return TowerDTO Объект DTO башни.
         */
        TowerDTO tower_to_dto(const ITower *tower) override;

        /**
         * @brief Преобразует DTO врага в объект врага.
         *
         * @param dto Объект DTO врага.
         * @return std::unique_ptr<IEnemy> Умный указатель на созданного врага.
         */
        std::unique_ptr<IEnemy> dto_to_enemy(const EnemyDTO &dto) override;

        /**
         * @brief Преобразует объект врага в DTO.
         *
         * @param enemy Указатель на объект врага.
         * @return EnemyDTO Объект DTO врага.
         */
        EnemyDTO enemy_to_dto(const IEnemy *enemy) override;

        /**
         * @brief Преобразует DTO замка в объект замка.
         *
         * @param dto Объект DTO замка.
         * @return std::unique_ptr<ICastle> Умный указатель на созданный замок.
         */
        std::unique_ptr<ICastle> dto_to_castle(const CastleDTO &dto) override;

        /**
         * @brief Преобразует объект замка в DTO.
         *
         * @param castle Указатель на объект замка.
         * @return CastleDTO Объект DTO замка.
         */
        CastleDTO castle_to_dto(const ICastle *castle) override;

        /**
         * @brief Деструктор репозитория.
         */
        ~MapperRepository() override = default;
    };
}