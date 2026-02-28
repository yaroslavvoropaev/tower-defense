#pragma once

#include "IEnemyRepository.h"

#include <unordered_map>
#include <functional>

namespace TowerDefense {
    /**
     * @brief Конкретная реализация репозитория для управления врагами.
     *
     * EnemyRepository хранит врагов в хэш-таблице, используя их ID в качестве ключей.
     * Предоставляет методы для добавления, удаления и поиска врагов.
     */
    class EnemyRepository final : public IEnemyRepository {
        std::unordered_map<ID, std::unique_ptr<IEnemy>> enemies_; ///< Хранилище врагов
    public:
        /**
         * @brief Конструктор репозитория врагов.
         */
        EnemyRepository() = default;

        /**
         * @brief Добавляет врага в репозиторий.
         *
         * @param enemy Умный указатель на объект врага.
         */
        void add_enemy(std::unique_ptr<IEnemy> enemy) override;

        /**
         * @brief Удаляет врага по идентификатору.
         *
         * @param id Идентификатор врага для удаления.
         */
        void delete_enemy(ID id) override;

        /**
         * @brief Возвращает врага по идентификатору.
         *
         * @param id Идентификатор врага.
         * @return IEnemy* Указатель на объект врага (не передает владение).
         */
        [[nodiscard]] IEnemy *get(ID id) override;

        /**
         * @brief Возвращает всех врагов в репозитории.
         *
         * @return std::vector<IEnemy*> Вектор указателей на всех врагов.
         */
        [[nodiscard]] std::vector<IEnemy*> get_all() override;

        /**
         * @brief Возвращает врагов в заданном радиусе от точки.
         *
         * @param center Центральная точка для поиска.
         * @param radius Радиус поиска.
         * @return std::vector<IEnemy*> Вектор указателей на врагов в радиусе.
         */
        [[nodiscard]] std::vector<IEnemy*> get_in_range(Point center, float radius) override;

        /**
         * @brief Находит цель по заданным критериям.
         *
         * @param comp Функция сравнения для определения лучшей цели.
         * @param filter Функция фильтрации для отсеивания неподходящих целей.
         * @return IEnemy* Указатель на найденную цель (не передает владение).
         */
        [[nodiscard]] IEnemy *find_target(
            std::function<bool(const std::unique_ptr<IEnemy> &, const std::unique_ptr<IEnemy> &)> comp,
            std::function<bool(const std::unique_ptr<IEnemy> &)> filter) const override;

        /**
         * @brief Очищает репозиторий (удаляет всех врагов).
         */
        void reset() override;

        /**
         * @brief Деструктор репозитория.
         */
        ~EnemyRepository() override = default;
    };
}