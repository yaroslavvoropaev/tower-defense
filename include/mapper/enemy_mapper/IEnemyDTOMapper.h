#pragma once

#include "IEnemy.h"
#include "dto.h"

namespace TowerDefense {
    /**
     * @brief Интерфейс маппера для преобразования объекта врага в DTO (Data Transfer Object).
     *
     * IEnemyDTOMapper отвечает за преобразование объектов типа IEnemy в
     * соответствующие объекты типа EnemyDTO. Используется для сериализации
     * состояния врагов, передачи данных между слоями приложения или сохранения
     * состояния в хранилище.
     */
    class IEnemyDTOMapper {
    public:
        /**
         * @brief Преобразует объект врага в DTO.
         *
         * @param enemy Указатель на объект врага для преобразования.
         * @return EnemyDTO - объект передачи данных, содержащий состояние врага.
         * @note Вызывающая сторона сохраняет владение объектом enemy.
         */
        virtual EnemyDTO transform(const IEnemy *enemy) = 0;

        /**
         * @brief Виртуальный деструктор для обеспечения корректного удаления производных классов.
         */
        virtual ~IEnemyDTOMapper() = default;
    };
}