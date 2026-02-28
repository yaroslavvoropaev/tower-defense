#pragma once

#include "dto.h"
#include "ILoader.h"

#include "ICastleRepository.h"
#include "IEnemyRepository.h"
#include "IStrategyRepository.h"
#include "ITowerRepository.h"

#include "IEffectFactory.h"
#include "IEnemyFactory.h"
#include "ITowerFactory.h"

#include "IID_service.h"
#include "IEconomyService.h"
#include "IMapperRepository.h"
#include "IEnemyService.h"
#include "ITowerService.h"
#include "IMoveService.h"

#include "GameFiled.h"
#include "IStateService.h"


namespace TowerDefense{

    class Loader : public ILoader {
        std::unique_ptr<IEnemyRepository> enemy_repository_;
        std::unique_ptr<ICastleRepository> castle_repository_;
        std::unique_ptr<IStrategyRepository> strategy_repository_;
        std::unique_ptr<IMapperRepository> mapper_repository_;
        std::unique_ptr<ITowerRepository> tower_repository_;

        std::unique_ptr<IEffectFactory> effect_factory_;
        std::unique_ptr<ITowerFactory> tower_factory_;
        std::unique_ptr<IEnemyFactory> enemy_factory_;
        std::unique_ptr<ICastleFactory> castle_factory_;

        std::unique_ptr<IID_service> id_service_;
        std::unique_ptr<IEnemyService> enemy_service_;
        std::unique_ptr<ITowerService> tower_service_;
        std::unique_ptr<IEconomyService> economy_service_;
        std::unique_ptr<IMoveService> move_service_;
        std::unique_ptr<IStateService> state_service_;

        std::unique_ptr<GameFiled> game_filed_;
        std::unique_ptr<IPresenter> presenter_;
    public:
        Loader() = default;
        IStateService &get_state_service() override;
        IPresenter &get_presenter() override;
        IMoveService &get_move_service() override;
        GameFiled &get_game_filed() override;
        IEconomyService &get_economy_service() override;
        ITowerService &get_tower_service() override;
        IEnemyService &get_enemy_service() override;
        IEnemyFactory &get_enemy_factory() override;
        ITowerRepository &get_tower_repository() override;
        IID_service &get_id_service() override;
        IEffectFactory &get_effect_factory() override;
        ITowerFactory &get_tower_factory() override;
        IEnemyRepository &get_enemy_repository() override;
        ICastleRepository &get_castle_repository() override;
        IStrategyRepository &get_strategy_repository() override;
        IMapperRepository &get_mapper_repository() override;

        TowerConfig load_tower_config(const std::string &path) override;
        EnemyDTO load_enemy_config(const std::string &path) override;
        CastleDTO load_castle_config(const std::string &path) override;
        EffectConfig load_effect_config(const std::string &path) override;
        LevelConfig load_level_config(const std::string &path) override;
        ICastleFactory& get_castle_factory() override;
        ~Loader() override = default ;
    };
}
