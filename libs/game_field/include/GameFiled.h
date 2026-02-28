#pragma once

#include "Matrix.h"


namespace TowerDefense {
    /**
     * @brief Структура, представляющая клетку игрового поля.
     */

    struct Cell {
        std::string landscape_type;
    };

    /**
     * @brief Класс, представляющий игровое поле Tower Defense.
     *
     * GameFiled содержит матрицу клеток и предоставляет методы для доступа
     * и управления состоянием игрового поля.
     */
    class GameFiled {
        Matrix<Cell> field; ///< Матрица клеток игрового поля
    public:
        /**
         * @brief Конструктор игрового поля.
         *
         * @param width Ширина поля (количество столбцов).
         * @param height Высота поля (количество строк).
         */
        GameFiled(int width, int height) : field(height, width) {}

        /**
         * @brief Возвращает ширину игрового поля.
         *
         * @return size_t Количество столбцов в поле.
         */
        [[nodiscard]] size_t get_width() const;

        /**
         * @brief Возвращает высоту игрового поля.
         *
         * @return size_t Количество строк в поле.
         */
        [[nodiscard]] size_t get_height() const;

        /**
         * @brief Возвращает клетку по указанным координатам.
         *
         * @param row Номер строки (начиная с 0).
         * @param col Номер столбца (начиная с 0).
         * @return Cell Клетка игрового поля.
         */
        [[nodiscard]] Cell get_cell(size_t row, size_t col) const;

        /**
         * @brief Устанавливает клетку по указанным координатам.
         *
         * @param row Номер строки (начиная с 0).
         * @param col Номер столбца (начиная с 0).
         * @param cell Новая клетка для установки.
         */
        void set_cell(size_t row, size_t col, const Cell &cell);
    };
}
