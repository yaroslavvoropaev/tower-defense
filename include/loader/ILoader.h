#pragma once

#include "dto.h"

#include "ICastleRepository.h"
#include "IEnemyRepository.h"
#include "IStrategyRepository.h"
#include "ITowerRepository.h"
#include "IMapperRepository.h"

#include "IEffectFactory.h"
#include "IEnemyFactory.h"
#include "ITowerFactory.h"
#include "ICastleFactory.h"

#include "IID_service.h"
#include "IEconomyService.h"
#include "IEnemyService.h"
#include "ITowerService.h"
#include "IMoveService.h"
#include "IStateService.h"

#include "GameFiled.h"
#include "IPresenter.h"



namespace TowerDefense {
    /**
     * @brief Интерфейс загрузчика игровых компонентов и конфигураций.
     *
     * ILoader предоставляет единую точку доступа ко всем основным сервисам,
     * фабрикам, репозиториям и методам загрузки конфигураций игры.
     */
    class ILoader {
    public:
        /**
         * @brief Возвращает фабрику для создания замков.
         * @return Ссылка на интерфейс ICastleFactory.
         */
        virtual ICastleFactory &get_castle_factory() = 0;
        /**
         * @brief Возвращает сервис управления состоянием игры.
         * @return Ссылка на интерфейс IStateService.
         */
        virtual IStateService &get_state_service() = 0;
        /**
         * @brief Возвращает презентер для отображения игрового состояния.
         * @return Ссылка на интерфейс IPresenter.
         */
        virtual IPresenter &get_presenter() = 0;
        /**
         * @brief Возвращает сервис управления перемещением объектов.
         * @return Ссылка на интерфейс IMoveService.
         */
        virtual IMoveService &get_move_service() = 0;
        /**
         * @brief Возвращает объект игрового поля.
         * @return Ссылка на объект GameFiled.
         */
        virtual GameFiled &get_game_filed() = 0;
        /**
         * @brief Возвращает сервис экономики.
         * @return Ссылка на интерфейс IEconomyService.
         */
        virtual IEconomyService &get_economy_service() = 0;
        /**
         * @brief Возвращает сервис управления башнями.
         * @return Ссылка на интерфейс ITowerService.
         */
        virtual ITowerService &get_tower_service() = 0;
        /**
         * @brief Возвращает сервис управления врагами.
         * @return Ссылка на интерфейс IEnemyService.
         */
        virtual IEnemyService &get_enemy_service() = 0;
        /**
         * @brief Возвращает фабрику для создания врагов.
         * @return Ссылка на интерфейс IEnemyFactory.
         */
        virtual IEnemyFactory &get_enemy_factory() = 0;
        /**
         * @brief Возвращает репозиторий башен.
         * @return Ссылка на интерфейс ITowerRepository.
         */
        virtual ITowerRepository &get_tower_repository() = 0;
        /**
         * @brief Возвращает сервис генерации уникальных идентификаторов.
         * @return Ссылка на интерфейс IID_service.
         */
        virtual IID_service &get_id_service() = 0;
        /**
         * @brief Возвращает фабрику эффектов.
         * @return Ссылка на интерфейс IEffectFactory.
         */
        virtual IEffectFactory &get_effect_factory() = 0;
        /**
         * @brief Возвращает фабрику для создания башен.
         * @return Ссылка на интерфейс ITowerFactory.
         */
        virtual ITowerFactory &get_tower_factory() = 0;
        /**
         * @brief Возвращает репозиторий врагов.
         * @return Ссылка на интерфейс IEnemyRepository.
         */
        virtual IEnemyRepository &get_enemy_repository() = 0;
        /**
         * @brief Возвращает репозиторий замков.
         * @return Ссылка на интерфейс ICastleRepository.
         */
        virtual ICastleRepository &get_castle_repository() = 0;
        /**
         * @brief Возвращает репозиторий стратегий.
         * @return Ссылка на интерфейс IStrategyRepository.
         */
        virtual IStrategyRepository &get_strategy_repository() = 0;
        /**
         * @brief Возвращает репозиторий мапперов.
         * @return Ссылка на интерфейс IMapperRepository.
         */
        virtual IMapperRepository &get_mapper_repository() = 0;
        /**
         * @brief Загружает конфигурацию башни из файла.
         * @param path Путь к файлу конфигурации.
         * @return Объект TowerConfig с параметрами башни.
         */
        virtual TowerConfig load_tower_config(const std::string &path) = 0;
        /**
         * @brief Загружает конфигурацию врага из файла.
         * @param path Путь к файлу конфигурации.
         * @return Объект EnemyDTO с параметрами врага.
         */
        virtual EnemyDTO load_enemy_config(const std::string &path) = 0;
        /**
         * @brief Загружает конфигурацию замка из файла.
         * @param path Путь к файлу конфигурации.
         * @return Объект CastleDTO с параметрами замка.
         */
        virtual CastleDTO load_castle_config(const std::string &path) = 0;
        /**
         * @brief Загружает конфигурацию эффекта из файла.
         * @param path Путь к файлу конфигурации.
         * @return Объект EffectConfig с параметрами эффекта.
         */
        virtual EffectConfig load_effect_config(const std::string &path) = 0;
        /**
         * @brief Загружает конфигурацию уровня из файла.
         * @param path Путь к файлу конфигурации.
         * @return Объект LevelConfig с параметрами уровня.
         */
        virtual LevelConfig load_level_config(const std::string &path) = 0;
        /**
         * @brief Виртуальный деструктор для обеспечения корректного удаления производных классов.
         */
        virtual ~ILoader() = default;
    };
}