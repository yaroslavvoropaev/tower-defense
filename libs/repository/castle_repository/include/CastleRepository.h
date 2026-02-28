#pragma once

#include "ICastleRepository.h"

#include <memory>

namespace TowerDefense {
    /**
     * @brief Конкретная реализация репозитория для управления замками.
     *
     * CastleRepository хранит единственный объект замка и предоставляет
     * методы для его добавления и получения.
     */
    class CastleRepository final : public ICastleRepository {
        std::unique_ptr<ICastle> castle_; ///< Умный указатель на объект замка

    public:
        /**
         * @brief Конструктор репозитория замков.
         */
        explicit CastleRepository() = default;

        /**
         * @brief Добавляет замок в репозиторий.
         *
         * @param castle Умный указатель на объект замка.
         */
        void add_castle(std::unique_ptr<ICastle> castle) override;

        /**
         * @brief Возвращает указатель на текущий замок.
         *
         * @return ICastle* Указатель на объект замка (не передает владение).
         */
        [[nodiscard]] ICastle *get() override;

        /**
         * @brief Деструктор репозитория.
         */
        ~CastleRepository() override = default;
    };
}