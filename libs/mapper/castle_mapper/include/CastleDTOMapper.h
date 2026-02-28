#pragma once

#include "ICastleDtoMapper.h"

namespace TowerDefense {
    /**
     * @brief Конкретная реализация маппера для преобразования замков в DTO.
     *
     * CastleDTOMapper преобразует объекты типа ICastle в объекты типа CastleDTO.
     */
    class CastleDTOMapper final : public ICastleDTOMapper {
    public:
        /**
         * @brief Конструктор маппера.
         */
        CastleDTOMapper() = default;

        /**
         * @brief Преобразует объект замка в DTO.
         *
         * Извлекает все необходимые данные из объекта замка и создает DTO.
         *
         * @param castle Указатель на объект замка для преобразования.
         * @return CastleDTO Объект передачи данных с состоянием замка.
         */
        CastleDTO transform(const ICastle *castle) override;

        /**
         * @brief Деструктор маппера.
         */
        ~CastleDTOMapper() override = default;
    };
}