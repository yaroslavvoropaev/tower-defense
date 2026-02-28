#pragma once

#include "IEnemy.h"
#include "ICastle.h"
#include "AbstractTower.h"
#include "dto.h"
#include "IEnemyDTOMapper.h"
#include "IEnemyMapper.h"
#include "ICastleDtoMapper.h"
#include "ICastleMapper.h"
#include "ITowerDTOMapper.h"
#include "ITowerMapper.h"
#include <typeindex>

namespace TowerDefense {
    /**
     * @brief Интерфейс репозитория для управления мапперами объектов.
     *
     * IMapperRepository служит централизованным хранилищем для всех мапперов
     * (преобразователей) между объектами и DTO. Реализует паттерн
     * "Репозиторий" для регистрации и получения мапперов.
     */
    class IMapperRepository {
    public:
        virtual ~IMapperRepository() = default;

        /**
         * @brief Регистрирует маппер для создания врагов из DTO.
         *
         * @param mapper Умный указатель на маппер врагов.
         */
        virtual void add_enemy_mapper(std::unique_ptr<IEnemyMapper> mapper) = 0;

        /**
         * @brief Регистрирует маппер для преобразования врагов в DTO.
         *
         * @param mapper Умный указатель на DTO-маппер врагов.
         */
        virtual void add_enemy_dto_mapper(std::unique_ptr<IEnemyDTOMapper> mapper) = 0;

        /**
         * @brief Регистрирует маппер для создания замков из DTO.
         *
         * @param mapper Умный указатель на маппер замков.
         */
        virtual void add_castle_mapper(std::unique_ptr<ICastleMapper> mapper) = 0;

        /**
         * @brief Регистрирует маппер для преобразования замков в DTO.
         *
         * @param mapper Умный указатель на DTO-маппер замков.
         */
        virtual void add_castle_dto_mapper(std::unique_ptr<ICastleDTOMapper> mapper) = 0;

        /**
         * @brief Регистрирует маппер для создания башен из DTO.
         *
         * @param name Имя типа башни.
         * @param mapper Умный указатель на маппер башен.
         */
        virtual void add_tower_mapper(std::string name, std::unique_ptr<ITowerMapper> mapper) = 0;

        /**
         * @brief Регистрирует маппер для преобразования башен в DTO.
         *
         * @param type_index Индекс типа башни для идентификации маппера.
         * @param mapper Умный указатель на DTO-маппер башен.
         */
        virtual void add_tower_dto_mapper(std::type_index type_index, std::unique_ptr<ITowerDTOMapper> mapper) = 0;


        /**
         * @brief Преобразует DTO башни в объект башни.
         *
         * @param dto Объект DTO башни.
         * @return std::unique_ptr<ITower> Умный указатель на созданную башню.
         */
        virtual std::unique_ptr<ITower> dto_to_tower(const TowerDTO &dto) = 0;

        /**
         * @brief Преобразует объект башни в DTO.
         *
         * @param tower Указатель на объект башни.
         * @return TowerDTO Объект DTO башни.
         */
        virtual TowerDTO tower_to_dto(const ITower *tower) = 0;

        /**
         * @brief Преобразует DTO врага в объект врага.
         *
         * @param dto Объект DTO врага.
         * @return std::unique_ptr<IEnemy> Умный указатель на созданного врага.
         */
        virtual std::unique_ptr<IEnemy> dto_to_enemy(const EnemyDTO &dto) = 0;

        /**
         * @brief Преобразует объект врага в DTO.
         *
         * @param enemy Указатель на объект врага.
         * @return EnemyDTO Объект DTO врага.
         */
        virtual EnemyDTO enemy_to_dto(const IEnemy *enemy) = 0;

        /**
         * @brief Преобразует DTO замка в объект замка.
         *
         * @param dto Объект DTO замка.
         * @return std::unique_ptr<ICastle> Умный указатель на созданный замок.
         */
        virtual std::unique_ptr<ICastle> dto_to_castle(const CastleDTO &dto) = 0;

        /**
         * @brief Преобразует объект замка в DTO.
         *
         * @param castle Указатель на объект замка.
         * @return CastleDTO Объект DTO замка.
         */
        virtual CastleDTO castle_to_dto(const ICastle *castle) = 0;

    };
}