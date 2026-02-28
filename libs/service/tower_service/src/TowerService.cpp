#include "TowerService.h"

#include <execution>
#include <vector>
#include <thread>
#include <algorithm>
#include <iostream>
#include <utility>

std::vector<TowerDefense::AttackInfo> TowerDefense::TowerService::attack_all(float dt) {
    std::vector<AttackInfo> res;
    std::vector<ITower *> towers = tower_repository_.get_all();
    for (auto tower : towers) {
        auto it = visitors_.find(typeid(*tower));
        IAttackVisitor *visitor = it->second.get();
        AttackInfo attack_info = tower->accept_attack_visitor(*visitor, dt);
        if (attack_info.tower_id != 0) {
            res.push_back(attack_info);
        }
    }
    auto castle = castle_repository_.get();
    auto enemies = enemy_repository_.get_all();
    for (auto enemy : enemies) {
        enemy->update(dt);
        if (enemy->get_health() <= 0) {
            castle->add_gold(enemy->get_gold());
            enemy_repository_.delete_enemy(enemy->get_ID());
        }
    }
    return res;
}


void TowerDefense::TowerService::add_visitor(std::type_index type, std::unique_ptr<IAttackVisitor> visitor) {
    visitors_.emplace(type, std::move(visitor));
}


std::vector<TowerDefense::AttackInfo> TowerDefense::TowerService::attack_all_par(float dt) {
    std::vector<ITower*> towers = tower_repository_.get_all();
    std::vector<AttackInfo> result;

    if (towers.empty()) {
        return result;
    }

    unsigned int num_threads = std::thread::hardware_concurrency();
    if (num_threads == 0) {
        num_threads = 4;
    }

    num_threads = std::min<unsigned int>(num_threads, towers.size());
    std::vector<std::vector<AttackInfo>> thread_results(num_threads);
    std::vector<std::thread> threads;

    auto worker = [this, dt, &thread_results] (size_t thread_index, std::vector<ITower*>::iterator begin, std::vector<ITower*>::iterator end){
        auto &local_res = thread_results[thread_index];

        for (auto it = begin; it != end; ++it) {
            ITower* tower = *it;

            auto visitor_it = visitors_.find(typeid(*tower));
            IAttackVisitor &visitor = *visitor_it->second;
            AttackInfo info = tower->accept_attack_visitor(visitor, dt);

            if (info.tower_id != 0) {
                local_res.push_back(std::move(info));
            }
        }
    };


    const size_t towers_per_thread = towers.size() / num_threads;
    auto start = towers.begin();

    for (size_t i = 0; i < num_threads - 1; ++i) {
        auto end = start + towers_per_thread;
        threads.emplace_back(worker, i, start, end);
        start = end;
    }

    threads.emplace_back(worker, num_threads - 1, start, towers.end());

    for (auto &thread : threads) {
        thread.join();
    }

    for (auto &vec : thread_results) {
        result.insert(result.end(),std::make_move_iterator(vec.begin()),std::make_move_iterator(vec.end()));
    }

    auto castle = castle_repository_.get();
    auto enemies = enemy_repository_.get_all();

    std::vector<ID> enemies_to_delete;

    for (auto *enemy : enemies) {
        enemy->update(dt);
        if (enemy->get_health() <= 0) {
            castle->add_gold(enemy->get_gold());
            enemies_to_delete.push_back(enemy->get_ID());
        }
    }

    for (auto id : enemies_to_delete) {
        enemy_repository_.delete_enemy(id);
    }
    return result;
}
