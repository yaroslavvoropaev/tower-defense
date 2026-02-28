#pragma once

#include "IEnemy.h"

#include <vector>
#include <functional>

namespace TowerDefense {
    /**
     * @brief Интерфейс репозитория для управления врагами.
     *
     * IEnemyRepository определяет методы для хранения, поиска и управления
     * объектами врагов. Поддерживает сложные запросы с фильтрацией и поиском
     * по различным критериям.
     */
    class IEnemyRepository {
    public:
        virtual ~IEnemyRepository() = default;

        /**
         * @brief Добавляет врага в репозиторий.
         *
         * @param enemy Умный указатель на объект врага.
         *              Владение объектом передается репозиторию.
         */
        virtual void add_enemy(std::unique_ptr<IEnemy> enemy) = 0;

        /**
         * @brief Удаляет врага по идентификатору.
         *
         * @param id Идентификатор врага для удаления.
         */
        virtual void delete_enemy(ID id) = 0;

        /**
         * @brief Возвращает врага по идентификатору.
         *
         * @param id Идентификатор врага.
         * @return IEnemy* Указатель на объект врага (не передает владение).
         */
        [[nodiscard]] virtual IEnemy *get(ID id) = 0;

        /**
         * @brief Возвращает всех врагов в репозитории.
         *
         * @return std::vector<IEnemy*> Вектор указателей на всех врагов.
         */
        [[nodiscard]] virtual std::vector<IEnemy *> get_all() = 0;

        /**
         * @brief Возвращает врагов в заданном радиусе от точки.
         *
         * @param center Центральная точка для поиска.
         * @param range Радиус поиска.
         * @return std::vector<IEnemy*> Вектор указателей на врагов в радиусе.
         */
        [[nodiscard]] virtual std::vector<IEnemy *> get_in_range(Point center, float range) = 0;

        /**
         * @brief Находит цель по заданным критериям.
         *
         * Использует функции сравнения и фильтрации для выбора цели.
         *
         * @param comp Функция сравнения для определения цели.
         * @param filter Функция фильтрации для отсеивания неподходящих целей.
         * @return IEnemy* Указатель на найденную цель (не передает владение).
         */
        [[nodiscard]] virtual IEnemy *find_target(
            std::function<bool(const std::unique_ptr<IEnemy> &, const std::unique_ptr<IEnemy> &)> comp,
            std::function<bool(const std::unique_ptr<IEnemy> &)> filter) const = 0;

        /**
         * @brief Очищает репозиторий (удаляет всех врагов).
         */
        virtual void reset() = 0;
    };
}