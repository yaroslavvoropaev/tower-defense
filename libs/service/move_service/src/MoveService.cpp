#include "MoveService.h"
#include <cmath>
#include <vector>
#include <thread>
#include <algorithm>
#include <execution>
#include <iostream>




void TowerDefense::MoveService::move(float dt) {
    for (auto &enemy : enemy_repository_.get_all()) {
        Point target_tile{};
        auto it = next_tile_map_.find(enemy->get_position());
        if (it != next_tile_map_.end()) {
            target_tile = it->second;
        } else {
            target_tile = path_[0];
        }

        float target_x = static_cast<float>(target_tile.x_) * tile_size;
        float target_y = static_cast<float>(target_tile.y_) * tile_size;

        float dx = target_x - enemy->get_x_pixels();
        float dy = target_y - enemy->get_y_pixels();
        float distance = std::sqrt(dx * dx + dy * dy);

        if (distance < enemy->get_speed() * dt * 1.5f) {
            enemy->set_x_pixels(target_x);
            enemy->set_y_pixels(target_y);
            enemy->set_position(target_tile);
            continue;
        }

        if (distance > 0.01f) {
            dx /= distance;
            dy /= distance;

            float movement = enemy->get_speed() * dt;
            if (movement > distance) {
                movement = distance;
            }
            enemy->set_x_pixels(enemy->get_x_pixels() + dx * movement);
            enemy->set_y_pixels(enemy->get_y_pixels() + dy * movement);
        }
    }
}



void TowerDefense::MoveService::move_par(float dt) {
    auto enemies = enemy_repository_.get_all();
    if (enemies.empty()) return;

    auto process_enemies = [this, dt](std::vector<IEnemy *>::iterator begin, std::vector<IEnemy *>::iterator end) {
        for (auto it = begin; it != end; ++it) {
            auto enemy = *it;
            Point target_tile;
            auto iterator = next_tile_map_.find(enemy->get_position());
            if (iterator != next_tile_map_.end()) {
                target_tile = iterator->second;
            } else {
                target_tile = path_[0];
            }

            float target_x = static_cast<float>(target_tile.x_) * tile_size;
            float target_y = static_cast<float>(target_tile.y_) * tile_size;

            float dx = target_x - enemy->get_x_pixels();
            float dy = target_y - enemy->get_y_pixels();
            float distance = std::sqrt(dx * dx + dy * dy);

            if (distance < enemy->get_speed() * dt * 1.5f) {
                enemy->set_x_pixels(target_x);
                enemy->set_y_pixels(target_y);
                enemy->set_position(target_tile);
                continue;
            }

            if (distance > 0.01f) {
                dx /= distance;
                dy /= distance;

                float movement = enemy->get_speed() * dt;
                if (movement > distance) {
                    movement = distance;
                }
                enemy->set_x_pixels(enemy->get_x_pixels() + dx * movement);
                enemy->set_y_pixels(enemy->get_y_pixels() + dy * movement);
            }
        }
    };


    std::vector<std::thread> threads;
    size_t chunk_size = enemies.size() / num_threads_;
    auto start = enemies.begin();
    for (unsigned int i = 0; i < num_threads_; ++i) {
        auto end = (i == num_threads_ - 1) ? enemies.end() : start + chunk_size;
        threads.emplace_back(process_enemies, start, end);
        start = end;
    }

    for (auto &thread : threads) {
        thread.join();
    }
}
