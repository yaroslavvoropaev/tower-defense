#pragma once

#include "IMoveService.h"
#include "IEnemyRepository.h"
#include "GameFiled.h"
#include <vector>
#include <functional>
#include <thread>

namespace TowerDefense{
    /**
     * @class MoveService
     * @brief Сервис для управления перемещением врагов по игровому полю.
     *
     * Обеспечивает движение врагов по предварительно рассчитанному пути,
     * поддерживает как последовательное, так и параллельное выполнение.
     * Путь вычисляется на основе типа ландшафта "road" на игровом поле.
     */
    class MoveService final : public IMoveService {
        const float tile_size = 64.0f;                 ///< Размер одной клетки игрового поля в пикселях
        IEnemyRepository &enemy_repository_;           ///< Репозиторий для доступа к данным врагов
        GameFiled &game_filed_;                        ///< Игровое поле с информацией о ландшафте
        std::vector<Point> path_;                      ///< Предварительно рассчитанный путь движения
        std::unordered_map<Point, Point, PointHash> next_tile_map_; ///< Карта переходов между точками пути
        size_t num_threads_ = std::thread::hardware_concurrency(); ///< Количество потоков для параллельных вычислений

    public:
        /**
         * @brief Конструктор сервиса движения.
         * @param enemy_repository  Репозиторий врагов
         * @param game_filed       Игровое поле
         *
         * При создании автоматически вычисляет путь движения по полю,
         * Путь строится только по клеткам с типом ландшафта "road".
         */
        explicit MoveService(IEnemyRepository &enemy_repository, GameFiled &game_filed) :
            enemy_repository_(enemy_repository),
            game_filed_(game_filed)
        {
            Point last_point{game_filed.get_width(), game_filed.get_height()};
            Point last_last_point = last_point;
            Point p{};

            while (p.x_ != game_filed.get_width() - 1 || p.y_ != game_filed_.get_height() - 1) {
                if (game_filed_.get_cell(p.y_, p.x_ + 1).landscape_type == "road") {
                    p = Point(p.x_ + 1, p.y_);
                    path_.push_back(p);
                } else if (game_filed_.get_cell(p.y_ + 1, p.x_).landscape_type == "road"  && last_last_point != Point(p.x_, p.y_ + 1)) {
                    p = Point(p.x_, p.y_ + 1);
                    path_.push_back(p);
                } else if (game_filed_.get_cell(p.y_ - 1, p.x_).landscape_type == "road" && last_last_point != Point(p.x_, p.y_ - 1)) {
                    p = Point(p.x_,p.y_ - 1);
                    path_.push_back(p);
                }
                last_last_point = last_point;
                last_point = p;
            }

            for (size_t i = 0; i < path_.size() - 1; ++i) {
                next_tile_map_[path_[i]] = path_[i + 1];
            }

            if (!path_.empty()) {
                next_tile_map_[path_.back()] = path_.back();
            }
        }

        /**
         * @brief Перемещает всех врагов параллельно.
         * @param dt  Время, прошедшее с предыдущего обновления.
         */
        void move_par(float dt) override;

        /**
         * @brief Перемещает всех врагов последовательно.
         * @param dt  Время, прошедшее с предыдущего обновления.
         */
        void move(float dt) override;

        ~MoveService() override = default;
    };
}