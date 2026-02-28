#pragma once

#include "dto.h"

namespace TowerDefense {
    /**
     * @brief Интерфейс презентера для управления представлением игры.
     *
     * IPresenter служит промежуточным слоем между игровой логикой и представлением.
     * Реализует паттерн "Presenter", предоставляя методы
     * для управления игровым состоянием и получения данных для отображения.
     */
    class IPresenter {
    public:
        virtual ~IPresenter() = default;

        /**
         * @brief Возвращает DTO с информацией о игровом поле.
         *
         * @return MapDto Структура с данными о карте.
         */
        [[nodiscard]] virtual MapDto get_map() const = 0;

        /**
         * @brief Возвращает DTO всех врагов на поле.
         *
         * @return std::vector<EnemyDTO> Вектор DTO врагов.
         */
        [[nodiscard]] virtual std::vector<EnemyDTO> get_enemies() const = 0;

        /**
         * @brief Возвращает DTO всех башен на поле.
         *
         * @return std::vector<TowerDTO> Вектор DTO башен.
         */
        [[nodiscard]] virtual std::vector<TowerDTO> get_towers() const = 0;

        /**
         * @brief Добавляет нового врага на игровое поле.
         *
         * Создает врага с параметрами по умолчанию и размещает его в начальной точке.
         */
        virtual void add_enemy() = 0;

        /**
         * @brief Обновляет позиции всех подвижных объектов.
         *
         * @param dt Время, прошедшее с предыдущего обновления (в секундах).
         */
        virtual void move(float dt) = 0;

        /**
         * @brief Выполняет атаки всех башен.
         *
         * @param dt Время, прошедшее с предыдущего обновления.
         * @return std::vector<AttackInfo> Информация о выполненых атаках.
         */
        [[nodiscard]] virtual std::vector<AttackInfo> tower_attack(float dt) = 0;

        /**
         * @brief Добавляет новую башню на игровое поле.
         *
         * @param type Тип башни.
         * @param x X-координата позиции башни.
         * @param y Y-координата позиции башни.
         */
        virtual void add_tower(const std::string &type, size_t x, size_t y) = 0;

        /**
         * @brief Возвращает DTO замка.
         *
         * @return CastleDTO Структура с данными о замке.
         */
        [[nodiscard]] virtual CastleDTO get_castle() const = 0;

        /**
         * @brief Выполняет атаки всех врагов.
         *
         * Обрабатывает логику атаки врагов по замку и башням.
         */
        virtual void enemy_attack() = 0;

        /**
         * @brief Улучшает башню по её идентификатору.
         *
         * @param id Идентификатор башни для улучшения.
         */
        virtual void upgrade_tower(ID id) = 0;

        /**
         * @brief Сбрасывает состояние игры к начальному.
         *
         * Удаляет всех врагов и башни, восстанавливает здоровье замка.
         */
        virtual void reset() = 0;

        /**
         * @brief Сохраняет текущее состояние игры.
         *
         * Записывает состояние игры (враги, башни, замок) в постоянное хранилище.
         */
        virtual void save() const = 0;

        /**
         * @brief Загружает сохраненное состояние игры.
         *
         * Восстанавливает состояние игры из постоянного хранилища.
         */
        virtual void load() const = 0;
    };
}