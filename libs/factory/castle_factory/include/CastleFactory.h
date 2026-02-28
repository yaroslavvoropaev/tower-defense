#pragma once

#include "IID_service.h"
#include "dto.h"
#include "Castle.h"
#include "ICastleFactory.h"

namespace TowerDefense {
    /**
     * @brief Конкретная реализация фабрики для создания замков.
     *
     * CastleFactory создает объекты типа Castle на основе конфигурации DTO
     * и сервиса генерации идентификаторов.
     */
    class CastleFactory final : public ICastleFactory {
        IID_service &id_service_;   ///< Ссылка на сервис генерации ID
        CastleDTO castle_dto_;      ///< Конфигурация замка из DTO

    public:
        /**
         * @brief Конструктор фабрики замков.
         *
         * @param id_service Сервис для генерации уникальных идентификаторов.
         * @param dto Конфигурация замка в формате DTO.
         */
        CastleFactory(IID_service &id_service, const CastleDTO dto)
            : id_service_(id_service), castle_dto_(dto) {}

        /**
         * @brief Создает новый объект замка.
         *
         * Использует данные из DTO и генерирует новый ID через id_service_.
         *
         * @return std::unique_ptr<ICastle> Умный указатель на созданный замок.
         */
        [[nodiscard]] std::unique_ptr<ICastle> create_castle() const override;

        /**
         * @brief Деструктор фабрики замков.
         */
        ~CastleFactory() override = default;
    };
}