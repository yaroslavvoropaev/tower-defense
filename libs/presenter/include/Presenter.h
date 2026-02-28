#pragma once

#include "IPresenter.h"
#include "GameFiled.h"
#include "ICastleFactory.h"
#include "IEnemyRepository.h"
#include "IMapperRepository.h"
#include "IEnemyFactory.h"
#include "IMoveService.h"
#include "ITowerRepository.h"
#include "ITowerFactory.h"
#include "ICastleRepository.h"
#include "ITowerService.h"
#include "IEnemyService.h"
#include "IEconomyService.h"
#include "IStateService.h"
#include "IID_service.h"

namespace TowerDefense {
    /**
     * @brief Конкретная реализация презентера игры Tower Defense.
     *
     * Presenter является центральным компонентом, координирующим взаимодействие
     * между различными сервисами, репозиториями и фабриками. Реализует паттерн
     * "Presenter" для управления игровой логикой и представлением.
     */
    class Presenter : public IPresenter {
        GameFiled &game_filed_;                ///< Игровое поле
        ICastleRepository &castle_repository_; ///< Репозиторий замков
        ITowerRepository &tower_repository_;   ///< Репозиторий башен
        IEnemyRepository &enemy_repository_;   ///< Репозиторий врагов
        IMapperRepository &mapper_repository_; ///< Репозиторий мапперов

        ITowerFactory &tower_factory_;         ///< Фабрика башен
        IEnemyFactory &enemy_factory_;         ///< Фабрика врагов
        ICastleFactory &castle_factory_;       ///< Фабрика замков

        IMoveService &move_service_;           ///< Сервис перемещения
        ITowerService &tower_service_;         ///< Сервис атак башен
        IEnemyService &enemy_service_;         ///< Сервис атак врагов
        IEconomyService &economy_service_;     ///< Сервис экономики
        IStateService &state_service_;         ///< Сервис состояния игры
        IID_service &id_service_;              ///< Сервис генерации ID

    public:
        /**
         * @brief Конструктор презентера.
         *
         *
         * @param game_filed Ссылка на игровое поле.
         * @param castle_repository Ссылка на репозиторий замков.
         * @param tower_repository Ссылка на репозиторий башен.
         * @param enemy_repository Ссылка на репозиторий врагов.
         * @param mapper_repository Ссылка на репозиторий мапперов.
         * @param enemy_factory Ссылка на фабрику врагов.
         * @param tower_factory Ссылка на фабрику башен.
         * @param castle_factory Ссылка на фабрику замков.
         * @param move_service Ссылка на сервис перемещения.
         * @param tower_service Ссылка на сервис атак башен.
         * @param enemy_service Ссылка на сервис атак врагов.
         * @param economy_service Ссылка на сервис экономики.
         * @param state_service Ссылка на сервис состояния игры.
         * @param id_service Ссылка на сервис генерации ID.
         */
        explicit Presenter(GameFiled &game_filed,ICastleRepository &castle_repository, ITowerRepository &tower_repository, IEnemyRepository &enemy_repository, IMapperRepository &mapper_repository,
                            IEnemyFactory &enemy_factory, ITowerFactory &tower_factory, ICastleFactory &castle_factory, IMoveService &move_service, ITowerService &tower_service, IEnemyService &enemy_service,
                            IEconomyService &economy_service, IStateService &state_service, IID_service &id_service) :
            game_filed_(game_filed), castle_repository_(castle_repository), tower_repository_(tower_repository), enemy_repository_(enemy_repository), mapper_repository_(mapper_repository),
            tower_factory_(tower_factory), enemy_factory_(enemy_factory), castle_factory_(castle_factory), move_service_(move_service), tower_service_(tower_service), enemy_service_(enemy_service),
            economy_service_(economy_service), state_service_(state_service), id_service_(id_service) {};

        /**
         * @brief Возвращает DTO с информацией о игровом поле.
         *
         * @return MapDto Структура с данными о карте.
         */
        [[nodiscard]] MapDto get_map() const override;

        /**
         * @brief Возвращает DTO всех врагов на поле.
         *
         * @return std::vector<EnemyDTO> Вектор DTO врагов.
         */
        [[nodiscard]] std::vector<EnemyDTO> get_enemies() const override;

        /**
         * @brief Возвращает DTO всех башен на поле.
         *
         * @return std::vector<TowerDTO> Вектор DTO башен.
         */
        [[nodiscard]] std::vector<TowerDTO> get_towers() const override;

        /**
         * @brief Обновляет позиции всех подвижных объектов.
         *
         * @param dt Время, прошедшее с предыдущего обновления.
         */
        void move(float dt) override;

        /**
         * @brief Добавляет нового врага на игровое поле.
         */
        void add_enemy() override;

        /**
         * @brief Добавляет новую башню на игровое поле.
         *
         * @param type Тип башни.
         * @param x X-координата позиции башни.
         * @param y Y-координата позиции башни.
         */
        void add_tower(const std::string &type, size_t x, size_t y) override;

        /**
         * @brief Выполняет атаки всех башен.
         *
         * @param dt Время, прошедшее с предыдущего обновления.
         * @return std::vector<AttackInfo> Информация о выполненых атаках.
         */
        [[nodiscard]] std::vector<AttackInfo> tower_attack(float dt) override;

        /**
         * @brief Возвращает DTO замка.
         *
         * @return CastleDTO Структура с данными о замке.
         */
        [[nodiscard]] CastleDTO get_castle() const override;

        /**
         * @brief Выполняет атаки всех врагов.
         */
        void enemy_attack() override;

        /**
         * @brief Улучшает башню по её идентификатору.
         *
         * @param id Идентификатор башни для улучшения.
         */
        void upgrade_tower(ID id) override;

        /**
         * @brief Сбрасывает состояние игры к начальному.
         */
        void reset() override;

        /**
         * @brief Сохраняет текущее состояние игры.
         */
        void save() const override;

        /**
         * @brief Загружает сохраненное состояние игры.
         */
        void load() const override;

        /**
         * @brief Деструктор презентера.
         */
        ~Presenter() override = default;
    };
}