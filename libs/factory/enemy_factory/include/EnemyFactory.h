#pragma once

#include "IID_service.h"
#include "dto.h"
#include "Enemy.h"
#include "IEnemyFactory.h"

namespace TowerDefense {
    /**
     * @brief Конкретная реализация фабрики для создания врагов.
     *
     * EnemyFactory создает объекты типа Enemy на основе конфигурации DTO
     * и сервиса генерации идентификаторов.
     */
    class EnemyFactory final : public IEnemyFactory {
        IID_service &id_service_;   ///< Ссылка на сервис генерации ID
        std::unique_ptr<IEnemy> enemy; ///< Прототип врага для клонирования

    public:
        /**
         * @brief Конструктор фабрики врагов.
         *
         * Создает прототип врага на основе DTO, который будет использоваться
         * для создания копий через метод create_enemy().
         *
         * @param id_service Сервис для генерации уникальных идентификаторов.
         * @param dto Конфигурация врага в формате DTO.
         */
        EnemyFactory(IID_service &id_service, const EnemyDTO &dto)
            : id_service_(id_service) {
            enemy = std::make_unique<Enemy>(dto.id, dto.name, dto.gold, dto.health,
                                           dto.max_health, dto.speed, Point(dto.x, dto.y),
                                           dto.x_pixels, dto.y_pixels);
        }

        /**
         * @brief Создает нового врага.
         *
         * Клонирует прототип и устанавливает новый уникальный идентификатор.
         *
         * @return std::unique_ptr<IEnemy> Умный указатель на созданного врага.
         */
        [[nodiscard]] std::unique_ptr<IEnemy> create_enemy() const override;

        /**
         * @brief Деструктор фабрики врагов.
         */
        ~EnemyFactory() override = default;
    };
}