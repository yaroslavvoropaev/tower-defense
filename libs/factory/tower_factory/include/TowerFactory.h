#pragma once

#include "ITowerFactory.h"
#include "IStrategyRepository.h"
#include "IEffectFactory.h"
#include "ICastleRepository.h"
#include "IID_service.h"
#include "dto.h"
#include "MagicTrap.h"
#include "MagicTower.h"
#include "SimpleTower.h"

#include <unordered_map>
#include <string>

namespace TowerDefense {
    /**
     * @brief Конкретная реализация фабрики для создания башен.
     *
     * TowerFactory создает различные типы башен (SimpleTower, MagicTower, MagicTrap)
     * на основе конфигурации. Использует другие фабрики и репозитории для
     * создания сложных объектов.
     */
    class TowerFactory final : public ITowerFactory {
        IEffectFactory &effect_factory_;        ///< Фабрика эффектов
        IStrategyRepository &strategy_repository_; ///< Репозиторий стратегий
        ICastleRepository &castle_repository_;  ///< Репозиторий замков
        IID_service &id_service_;               ///< Сервис генерации ID
        std::unordered_map<std::string, size_t> costs_; ///< Стоимости башен по типам
        std::unordered_map<std::string, std::unique_ptr<ITower>> towers_; ///< Прототипы башен

    public:
        /**
         * @brief Конструктор фабрики башен.
         *
         * Инициализирует фабрику на основе конфигурации, создавая прототипы
         * башен для каждого типа, определенного в конфигурации.
         *
         * @param effect_factory Фабрика для создания эффектов.
         * @param strategy_repository Репозиторий стратегий выбора целей.
         * @param castle_repository Репозиторий замков.
         * @param id_service Сервис для генерации уникальных идентификаторов.
         * @param conf Конфигурация башен из файла конфигурации.
         */
        TowerFactory(IEffectFactory &effect_factory, IStrategyRepository &strategy_repository,
                     ICastleRepository &castle_repository, IID_service &id_service,
                     const TowerConfig &conf)
            : effect_factory_(effect_factory), strategy_repository_(strategy_repository),
              castle_repository_(castle_repository), id_service_(id_service) {

            for (auto &dto : conf.towers.at("simple_tower")) {
                towers_.emplace(dto.type, std::make_unique<SimpleTower>(
                    dto.id, dto.range, dto.level, Point(dto.x, dto.y),
                    strategy_repository_.get_strategy(dto.strategy),
                    std::stof(dto.properties.at("damage")),
                    std::stof(dto.properties.at("rate_of_fire"))
                ));
                costs_.emplace(dto.type, dto.cost);
            }

            for (auto &dto : conf.towers.at("magic_tower")) {
                towers_.emplace(dto.type, std::make_unique<MagicTower>(
                    dto.id, dto.range, dto.level, Point(dto.x, dto.y),
                    strategy_repository_.get_strategy(dto.strategy),
                    std::stof(dto.properties.at("damage")),
                    std::stof(dto.properties.at("rate_of_fire")),
                    effect_factory.create_effect(dto.properties.at("effect"))
                ));
                costs_.emplace(dto.type, dto.cost);
            }

            for (auto &dto : conf.towers.at("magic_trap")) {
                towers_.emplace(dto.type, std::make_unique<MagicTrap>(
                    dto.id, dto.range, dto.level, Point(dto.x, dto.y),
                    strategy_repository_.get_strategy(dto.strategy),
                    std::stof(dto.properties.at("rate_of_fire")),
                    effect_factory.create_effect(dto.properties.at("effect"))
                ));
                costs_.emplace(dto.type, dto.cost);
            }
        }

        /**
         * @brief Создает башню указанного типа в заданной позиции.
         *
         * @param type Строковый идентификатор типа башни.
         * @param point Позиция для размещения башни.
         * @return std::unique_ptr<ITower> Умный указатель на созданную башню.
         * @throw std::out_of_range выбрасывать исключения при некорректном типе башни.
         */
        [[nodiscard]] std::unique_ptr<ITower> create_tower(const std::string &type, const Point &point) const override;

        /**
         * @brief Деструктор фабрики башен.
         */
        ~TowerFactory() override = default;
    };
}