#pragma once

#include "ICastle.h"
#include <memory>

namespace TowerDefense {
    /**
     * @brief Интерфейс репозитория для управления замками.
     *
     * ICastleRepository определяет методы для хранения и доступа к объектам замков.
     * Реализует паттерн "Репозиторий", обеспечивая абстракцию над хранилищем данных.
     * Предполагает, что в игре существует только один замок.
     */
    class ICastleRepository {
    public:
        virtual ~ICastleRepository() = default;

        /**
         * @brief Добавляет замок в репозиторий.
         *
         * @param castle Умный указатель на объект замка.
         *              Владение объектом передается репозиторию.
         */
        virtual void add_castle(std::unique_ptr<ICastle> castle) = 0;

        /**
         * @brief Возвращает указатель на текущий замок.
         *
         * Предполагается, что в репозитории хранится только один замок.
         *
         * @return ICastle* Указатель на объект замка (не передает владение).
         */
        [[nodiscard]] virtual ICastle *get() = 0;
    };
}