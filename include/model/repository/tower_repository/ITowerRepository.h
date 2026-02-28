#pragma once

#include "AbstractTower.h"

namespace TowerDefense {
    /**
     * @brief Интерфейс репозитория для управления башнями.
     *
     * ITowerRepository определяет методы для хранения, поиска и управления
     * объектами башен. Реализует паттерн "Репозиторий", предоставляя
     * абстрактный интерфейс для доступа к данным башен.
     */
    class ITowerRepository {
    public:
        virtual ~ITowerRepository() = default;

        /**
         * @brief Добавляет башню в репозиторий.
         *
         * @param tower Умный указатель на объект башни.
         *              Владение объектом передается репозиторию.
         */
        virtual void add_tower(std::unique_ptr<ITower> tower) = 0;

        /**
         * @brief Возвращает башню по идентификатору.
         *
         * @param id Идентификатор башни.
         * @return ITower* Указатель на объект башни (не передает владение).
         */
        [[nodiscard]] virtual ITower *get(ID id) = 0;

        /**
         * @brief Возвращает все башни в репозитории.
         *
         * @return std::vector<ITower*> Вектор указателей на все башни.
         */
        [[nodiscard]] virtual std::vector<ITower *> get_all() = 0;

        /**
         * @brief Очищает репозиторий (удаляет все башни).
         *
         * Используется для сброса состояния игры или при завершении уровня.
         */
        virtual void reset() = 0;
    };
}