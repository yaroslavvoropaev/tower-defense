#pragma once

#include "ICastleMapper.h"

namespace TowerDefense {
    /**
     * @brief Конкретная реализация маппера для создания замков из DTO.
     *
     * CastleMapper создает объекты типа ICastle на основе данных из CastleDTO.
     */
    class CastleMapper final : public ICastleMapper {
    public:
        /**
         * @brief Конструктор маппера.
         */
        CastleMapper() = default;

        /**
         * @brief Создает объект замка на основе DTO.
         *
         * Использует данные из DTO для инициализации нового объекта замка.
         *
         * @param dto Объект передачи данных с параметрами замка.
         * @return std::unique_ptr<ICastle> Умный указатель на созданный объект замка.
         */
        std::unique_ptr<ICastle> transform(const CastleDTO &dto) override;

        /**
         * @brief Деструктор маппера.
         */
        ~CastleMapper() override = default;
    };
}