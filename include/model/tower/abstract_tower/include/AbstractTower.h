#pragma once

#include "Point.h"
#include "IEnemy.h"
#include "id.h"
#include "IStrategy.h"

#include <vector>
#include "dto.h"

namespace TowerDefense {
    class IUpgradeVisitor;
    class IAttackVisitor;

    /**
     * @brief Интерфейс, представляющий башню в игре Tower Defense.
     *
     * ITower определяет основные свойства и поведение башен: позицию, дальность
     * атаки, уровень, стратегию выбора целей и методы для обработки атак и улучшений
     * через паттерн "Посетитель".
     */
    class ITower {
    public:
        /**
         * @brief Возвращает позицию башни на игровом поле.
         * @return Текущая позиция башни.
         */
        [[nodiscard]] virtual Point get_position() const = 0;

        /**
         * @brief Устанавливает позицию башни на игровом поле.
         * @param position Новая позиция башни.
         */
        virtual void set_position(const Point &position) = 0;

        /**
         * @brief Возвращает дальность атаки башни.
         * @return Дальность атаки.
         */
        [[nodiscard]] virtual float get_range() const = 0;

        /**
         * @brief Устанавливает дальность атаки башни.
         * @param range Новая дальность атаки.
         */
        virtual void set_range(float range) = 0;

        /**
         * @brief Возвращает текущий уровень башни.
         * @return Уровень башни.
         */
        [[nodiscard]] virtual size_t get_level() const = 0;

        /**
         * @brief Устанавливает уровень башни.
         * @param level Новый уровень башни.
         */
        virtual void set_level(size_t level) = 0;

        /**
         * @brief Находит цели для атаки, используя текущую стратегию.
         * @return Вектор указателей на найденные цели (врагов).
         */
        virtual std::vector<IEnemy *> find_target() = 0;

        /**
         * @brief Принимает посетителя для обработки атаки.
         *
         * @param attack_visitor Посетитель, реализующий логику атаки.
         * @param dt Время, прошедшее с предыдущего обновления.
         * @return AttackInfo Информация о выполненной атаке.
         */
        virtual AttackInfo accept_attack_visitor(IAttackVisitor &attack_visitor, float dt) = 0;

        /**
         * @brief Принимает посетителя для обработки улучшения.
         *
         * @param upgrade_visitor Посетитель, реализующий логику улучшения.
         * @param level_dto DTO с информацией об уровне улучшения.
         */
        virtual void accept_upgrade_visitor(IUpgradeVisitor &upgrade_visitor, LevelDTO &level_dto) = 0;

        /**
         * @brief Возвращает уникальный идентификатор башни.
         * @return Идентификатор башни.
         */
        [[nodiscard]] virtual ID get_id() const = 0;

        /**
         * @brief Устанавливает уникальный идентификатор башни.
         * @param id Новый идентификатор.
         */
        virtual void set_ID(ID id) = 0;

        /**
         * @brief Возвращает текущую стратегию выбора целей.
         * @return Указатель на объект стратегии.
         */
        [[nodiscard]] virtual IStrategy *get_strategy() const = 0;

        /**
         * @brief Виртуальный деструктор для корректного наследования.
         */
        virtual ~ITower() = default;

        /**
         * @brief Создает глубокую копию башни.
         *
         * Реализует паттерн "Прототип".
         *
         * @return std::unique_ptr<ITower> Умный указатель на копию башни.
         */
        virtual std::unique_ptr<ITower> clone() = 0;

        /**
         * @brief Возвращает скорострельность башни (выстрелов в секунду).
         * @return Скорострельность башни.
         */
        [[nodiscard]] virtual float get_rate_of_fire() const = 0;

        /**
         * @brief Устанавливает скорострельность башни.
         * @param rate_of_fire Новая скорострельность.
         */
        virtual void set_rate_of_fire(float rate_of_fire) = 0;

        /**
         * @brief Пытается выполнить атаку, проверяя время перезарядки.
         *
         * @param dt Время, прошедшее с предыдущего обновления.
         * @return true, если атака выполнена; false, если башня на перезарядке.
         */
        virtual bool try_attack(float dt) = 0;
    };

    /**
     * @brief Абстрактный базовый класс для башен, реализующий общую функциональность.
     *
     * AbstractTower предоставляет реализацию общих методов интерфейса ITower
     * и может быть унаследован конкретными типами башен.
     */
    class AbstractTower : public ITower {
        ID id_;                 ///< Уникальный идентификатор башни
        float range_;           ///< Дальность атаки
        size_t level_;          ///< Текущий уровень башни
        Point location_;        ///< Позиция на игровом поле
        IStrategy *strategy_;   ///< Стратегия выбора целей
        float rate_of_fire_;    ///< Скорострельность (выстрелов в секунду)
        float cooldown_;        ///< Текущее время перезарядки

    public:
        /**
         * @brief Конструктор абстрактной башни.
         *
         * @param id Уникальный идентификатор башни.
         * @param range Дальность атаки.
         * @param level Начальный уровень башни.
         * @param location Начальная позиция башни.
         * @param strategy Стратегия выбора целей.
         * @param rate_of_fire Скорострельность башни.
         */
        AbstractTower(ID id, float range, size_t level, Point location, IStrategy *strategy, float rate_of_fire)
            : id_(id), range_(range), level_(level), location_(location),
              strategy_(strategy), rate_of_fire_(rate_of_fire), cooldown_(1/rate_of_fire) {}

        // Реализации методов интерфейса ITower

        /**
         * @brief Возвращает дальность атаки башни.
         * @return Дальность атаки.
         */
        [[nodiscard]] float get_range() const override;

        /**
         * @brief Устанавливает дальность атаки башни.
         * @param range Новая дальность атаки.
         */
        void set_range(float range) override;

        /**
         * @brief Возвращает текущий уровень башни.
         * @return Уровень башни.
         */
        [[nodiscard]] size_t get_level() const override;

        /**
         * @brief Устанавливает уровень башни.
         * @param level Новый уровень башни.
         */
        void set_level(size_t level) override;

        /**
         * @brief Находит цели для атаки, используя текущую стратегию.
         * @return Вектор указателей на найденные цели (врагов).
         */
        std::vector<IEnemy *> find_target() override;
        /**
         * @brief Возвращает текущую стратегию выбора целей.
         * @return Указатель на объект стратегии.
         */
        [[nodiscard]] IStrategy* get_strategy() const override;

        /**
         * @brief Принимает посетителя для обработки атаки.
         *
         * @param attack_visitor Посетитель, реализующий логику атаки.
         * @param dt Время, прошедшее с предыдущего обновления.
         * @return AttackInfo Информация о выполненной атаке.
         */
        AttackInfo accept_attack_visitor(IAttackVisitor &attack_visitor, float dt) override;

        /**
         * @brief Принимает посетителя для обработки улучшения.
         *
         * @param upgrade_visitor Посетитель, реализующий логику улучшения.
         * @param level_dto DTO с информацией об уровне улучшения.
         */
        void accept_upgrade_visitor(IUpgradeVisitor &upgrade_visitor, LevelDTO &level_dto) override;

        /**
         * @brief Возвращает позицию башни на игровом поле.
         * @return Текущая позиция башни.
         */
        [[nodiscard]] Point get_position() const override;

        /**
         * @brief Возвращает уникальный идентификатор башни.
         * @return Идентификатор башни.
         */
        [[nodiscard]] ID get_id() const override;

        /**
         * @brief Устанавливает уникальный идентификатор башни.
         * @param id Новый идентификатор.
         */
        void set_ID(ID id) override;

        /**
         * @brief Возвращает скорострельность башни (выстрелов в секунду).
         * @return Скорострельность башни.
         */
        [[nodiscard]] float get_rate_of_fire() const override;

        /**
         * @brief Устанавливает скорострельность башни.
         * @param rate_of_fire Новая скорострельность.
         */
        void set_rate_of_fire(float rate_of_fire) override;

        /**
         * @brief Пытается выполнить атаку, проверяя время перезарядки.
         *
         * Уменьшает время перезарядки на dt и возвращает true, если
         * перезарядка завершена и можно выполнить атаку.
         *
         * @param dt Время, прошедшее с предыдущего обновления.
         * @return true, если атака выполнена; false, если башня на перезарядке.
         */
        bool try_attack(float dt) override;

        /**
         * @brief Устанавливает позицию башни на игровом поле.
         * @param position Новая позиция башни.
         */
        void set_position(const Point& position) override;

        /**
         * @brief Виртуальный деструктор для корректного наследования.
         */
        ~AbstractTower() override = default;
    };
}