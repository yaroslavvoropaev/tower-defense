#pragma once

#include "ITowerRepository.h"
#include <unordered_map>

namespace TowerDefense {
    /**
     * @brief Конкретная реализация репозитория для управления башнями.
     *
     * TowerRepository хранит башни в хэш-таблице, используя их ID в качестве ключей.
     * Предоставляет методы для добавления, получения и управления башнями.
     */
    class TowerRepository final : public ITowerRepository {
        std::unordered_map<ID, std::unique_ptr<ITower>> towers_; ///< Хранилище башен

    public:
        /**
         * @brief Конструктор репозитория башен.
         */
        TowerRepository() = default;

        /**
         * @brief Добавляет башню в репозиторий.
         *
         * @param tower Умный указатель на объект башни.
         */
        void add_tower(std::unique_ptr<ITower> tower) override;

        /**
         * @brief Возвращает башню по идентификатору.
         *
         * @param id Идентификатор башни.
         * @return ITower* Указатель на объект башни (не передает владение).
         */
        [[nodiscard]] ITower* get(ID id) override {
            return towers_.at(id).get();
        }

        /**
         * @brief Возвращает все башни в репозитории.
         *
         * @return std::vector<ITower*> Вектор указателей на все башни.
         */
        [[nodiscard]] std::vector<ITower*> get_all() override;

        /**
         * @brief Очищает репозиторий (удаляет все башни).
         */
        void reset() override;

        /**
         * @brief Деструктор репозитория.
         */
        ~TowerRepository() override = default;
    };
}