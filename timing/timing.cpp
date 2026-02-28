#include <iostream>
#include <thread>

#include "Enemy.h"
#include "Loader.h"

#include "NearestToTower.h"
#include "SimpleTower.h"

int main() {
    int x = 0;
    std::thread th1([&](){ x += 1;});
    std::thread th2([&](){ x += 2;});
    th1.join();
    th2.join();

    std::unique_ptr<TowerDefense::ILoader> loader = std::make_unique<TowerDefense::Loader>();
    auto &move_service = loader->get_move_service();
    auto &enemy_repository = loader->get_enemy_repository();
    auto &tower_repository = loader->get_tower_repository();
    auto &tower_service = loader->get_tower_service();
    auto strategy = std::make_unique<TowerDefense::NearestToTower>(enemy_repository);

    size_t start_id = 100;
    size_t cnt_entity = 0;
    for (size_t i = 1; i < 5; ++i) {
        size_t per_size = 50;
        cnt_entity = cnt_entity + 50;
        for (size_t j = 1; j < cnt_entity; ++j) {
            auto tower = std::make_unique<TowerDefense::SimpleTower>(start_id, 7.0, 1, TowerDefense::Point(0, j), strategy.get(), 1, 1);
            tower_repository.add_tower(std::move(tower));
            start_id++;
            tower = std::make_unique<TowerDefense::SimpleTower>(start_id, 7.0, 1, TowerDefense::Point(2, j), strategy.get(), 1, 1);
            tower_repository.add_tower(std::move(tower));
            start_id++;
        }
        for (size_t j = 1; j < cnt_entity; ++j) {
            auto enemy = std::make_unique<TowerDefense::Enemy>(start_id, "enemy", 100, 5000.0, 5000.0, 500.0, TowerDefense::Point(j, 1), j * 64 + 32, 96);
            enemy_repository.add_enemy(std::move(enemy));
            start_id++;
        }
        size_t total_seq = 0;
        for (size_t j = 0; j < per_size; ++j) {
            auto start = std::chrono::steady_clock::now();
            move_service.move(0.016);
            tower_service.attack_all(0.5);
            auto end = std::chrono::steady_clock::now();
            total_seq += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        }

        enemy_repository.reset();
        tower_repository.reset();

        for (size_t j = 1; j < cnt_entity; ++j) {
            auto tower = std::make_unique<TowerDefense::SimpleTower>(start_id, 7.0, 1, TowerDefense::Point(0, j), strategy.get(), 1, 1);
            tower_repository.add_tower(std::move(tower));
            start_id++;
            tower = std::make_unique<TowerDefense::SimpleTower>(start_id, 7.0, 1, TowerDefense::Point(2, j), strategy.get(), 1, 1);
            tower_repository.add_tower(std::move(tower));
            start_id++;
        }
        for (size_t j = 1; j < cnt_entity; ++j) {
            auto enemy = std::make_unique<TowerDefense::Enemy>(start_id, "enemy", 100, 5000.0, 5000.0, 500.0, TowerDefense::Point(j, 1), j * 64 + 32, 96);
            enemy_repository.add_enemy(std::move(enemy));
            start_id++;
        }

        size_t total_par = 0;
        for (size_t j = 0; j < per_size; ++j) {
            auto start = std::chrono::steady_clock::now();
            move_service.move_par(0.016);
            tower_service.attack_all_par(0.5);
            auto end = std::chrono::steady_clock::now();
            total_par += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        }

        enemy_repository.reset();
        tower_repository.reset();
        std::cout << cnt_entity * 3 << " " <<  static_cast<double>(total_seq) / static_cast<double>(per_size) << " " << static_cast<double>(total_par) / static_cast<double>(per_size) << std::endl;
    }

    return 0;
}
