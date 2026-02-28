#pragma once

#include <string>

namespace TowerDefense {
    /**
     * @brief Интерфейс сервиса для управления сохранением и загрузкой состояния игры.
     *
     * IStateService предоставляет методы для сохранения и восстановления состояния
     * различных игровых объектов (врагов, замков, башен) в файлы. Реализует
     * механизмы сериализации и десериализации игрового состояния.
     */
    class IStateService {
    public:
        virtual ~IStateService() = default;

        /**
         * @brief Загружает состояние врагов из файла.
         *
         * @param path Путь к файлу с сохраненным состоянием врагов.
         */
        virtual void load_enemy(const std::string &path) = 0;

        /**
         * @brief Сохраняет состояние врагов в файл.
         *
         * @param path Путь к файлу для сохранения состояния врагов.
         */
        virtual void save_enemy(const std::string &path) = 0;

        /**
         * @brief Загружает состояние замка из файла.
         *
         * @param path Путь к файлу с сохраненным состоянием замка.
         */
        virtual void load_castle(const std::string &path) = 0;

        /**
         * @brief Сохраняет состояние замка в файл.
         *
         * @param path Путь к файлу для сохранения состояния замка.
         */
        virtual void save_castle(const std::string &path) = 0;

        /**
         * @brief Загружает состояние башен из файла.
         *
         * @param path Путь к файлу с сохраненным состоянием башен.
         */
        virtual void load_tower(const std::string &path) = 0;

        /**
         * @brief Сохраняет состояние башен в файл.
         *
         * @param path Путь к файлу для сохранения состояния башен.
         */
        virtual void save_tower(const std::string &path) = 0;
    };
}