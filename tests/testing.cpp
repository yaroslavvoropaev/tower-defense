#define CATCH_CONFIG_MAIN

#include "catch2/catch_all.hpp"

#include <string>
#include <iostream>

#include "Enemy.h"
#include "Matrix.h"
#include "PoisonEffect.h"
#include "SlowEffect.h"
#include "WeaknessEffect.h"
#include "Castle.h"

//towers
#include "SimpleTower.h"
#include "MagicTower.h"
#include "MagicTrap.h"

//strategy
#include "AllInRange.h"
#include "Strongest.h"
#include "Weakest.h"
#include "NearestToCastle.h"
#include "NearestToTower.h"

//repository
#include "MapperRepository.h"
#include "EnemyRepository.h"
#include "CastleRepository.h"
#include "TowerRepository.h"


//visitors
#include "SimpleTowerAttackVisitor.h"
#include "MagicTowerAttackVisitor.h"
#include "MagicTrapAttackVisitor.h"

#include "SimpleTowerUpgradeVisitor.h"
#include "MagicTowerUpgradeVisitor.h"
#include "MagicTrapUpgradeVisitor.h"

//service
#include "EconomyService.h"
#include "MoveService.h"
#include "TowerService.h"
#include "EnemyService.h"
#include "ID_service.h"

//factory
#include "CastleFactory.h"
#include "EffectFactory.h"
#include "EnemyFactory.h"
#include "StrategyRepository.h"
#include "TowerFactory.h"


//mapper
#include "CastleDTOMapper.h"
#include "CastleMapper.h"
#include "EnemyMapper.h"
#include "EnemyDTOMapper.h"
#include "SimpleTowerMapper.h"
#include "SimpleTowerDTOMapper.h"
#include "MagicTowerMapper.h"
#include "MagicTowerDTOMapper.h"
#include "MagicTrapMapper.h"
#include "MagicTrapDTOMapper.h"
#include "YamlStateService.h"


TEST_CASE("Matrix class testing") {
    SECTION("Matrix constructors") {
        SECTION("Default constructor") {
            Matrix<int> matrix{};
            REQUIRE(matrix.rows() == 0);
            REQUIRE(matrix.cols() == 0);
        }
        SECTION("Base constructor") {
            Matrix<int> matrix{5, 4, 2};
            REQUIRE(matrix.rows() == 5);
            REQUIRE(matrix.cols() == 4);
            for (int i : matrix) {
                REQUIRE(i == 2);
            }
        }
        SECTION("Copy constructor") {
            Matrix<int> matrix{5, 4, 2};
            Matrix<int> matrix2 = matrix;
            REQUIRE(matrix2 == matrix);
        }
        SECTION("Copy constructor") {
            Matrix<int> matrix{3, 2, 2};
            Matrix<int> matrix2{std::move(matrix)};
            REQUIRE(matrix2.rows() == 3);
            REQUIRE(matrix2.cols() == 2);
            for (int i : matrix) {
                REQUIRE(i == 2);
            }
        }

        SECTION("Copy operator =") {
            Matrix<int> matrix{};
            Matrix<int> matrix2{3, 2, 2};
            matrix = matrix2;
            REQUIRE(matrix == matrix2);
        }
        SECTION("Move operator =") {
            Matrix<int> matrix{1, 4};
            Matrix<int> matrix2{3, 2, 2};
            matrix = std::move(matrix2);
            REQUIRE(matrix.rows() == 3);
            REQUIRE(matrix.cols() == 2);
            for (int i : matrix) {
                REQUIRE(i == 2);
            }
        }
    }
    SECTION("Methods") {
        SECTION("base at") {
            Matrix<int> matrix{5, 4, 2};
            for (int i : matrix) {
                REQUIRE(i == 2);
            }
            REQUIRE_THROWS_AS(matrix.at(100), std::out_of_range);
        }
        SECTION("const at") {
            const Matrix<int> matrix{5, 4, 2};
            for (int i : matrix) {
                REQUIRE(i == 2);
            }
            REQUIRE_THROWS_AS(matrix.at(100), std::out_of_range);
        }
        SECTION("cbegin") {
            const Matrix<int> matrix{5, 4, 2};
            REQUIRE(*matrix.cbegin() == 2);
        }
        SECTION("cend") {
            const Matrix<int> matrix{5, 4, 2};
            REQUIRE(*(matrix.cend() - 1) == 2);
        }
        SECTION("operator ==") {
            Matrix<int> matrix{5, 4, 2};
            Matrix<int> matrix2{5, 4, 2};
            Matrix<int> matrix3{5, 3, 2};
            REQUIRE((matrix == matrix2) == true);
            REQUIRE((matrix == matrix3) == false);
        }
        SECTION("max_size") {
            Matrix<int> matrix{5, 4, 2};
            REQUIRE(matrix.max_size() == std::numeric_limits<size_t>::max());
        }
        SECTION("empty") {
            Matrix<int> matrix{};
            REQUIRE(matrix.empty() == true);
        }
        SECTION("emplace") {
            Matrix<int> matrix{5, 4, 2};
            matrix.emplace(matrix.cbegin() + 7, 11);
            REQUIRE(matrix.at(7) == 11);
            REQUIRE_THROWS_AS(matrix.emplace(matrix.cbegin() + 1000), std::out_of_range);
        }

        SECTION("insert by value") {
            Matrix<std::string> matrix{5, 4, "abc"};
            std::string str1{"a"};
            matrix.insert(matrix.cbegin(), str1);
            REQUIRE(matrix.at(0) == str1);
            std::string str2{"b"};
            matrix.insert(matrix.cbegin() + 3, std::move(str2));
            REQUIRE(matrix.at(3) == str2);
            matrix.insert(matrix.cbegin() + 15, 2, "c");
            REQUIRE_THROWS_AS(matrix.insert(matrix.cbegin() + 1000, 100, "c"), std::out_of_range);
            REQUIRE(matrix.at(15) == "c");
            REQUIRE(matrix.at(16) == "c");
        }
        SECTION("insert by iterators") {
            Matrix<int> matrix{5, 4, 10};
            std::vector<int> vec{0, 1, 2, 3};
            matrix.insert(matrix.cbegin() + 2, vec.begin(), vec.end());
            REQUIRE_THROWS_AS(matrix.insert(matrix.cbegin() + 1000, vec.begin(), vec.end()), std::out_of_range);
            REQUIRE(matrix.at(2) == vec.at(0));
            REQUIRE(matrix.at(3) == vec.at(1));
            REQUIRE(matrix.at(4) == vec.at(2));
            REQUIRE(matrix.at(5) == vec.at(3));
        }
        SECTION("insert by il") {
            Matrix<int> matrix{5, 4, 10};
            matrix.insert(matrix.cbegin() + 2, {0, 1, 2, 3});
            REQUIRE_THROWS_AS(matrix.insert(matrix.cbegin() + 1000, {0, 1, 2, 3}), std::out_of_range);
            REQUIRE(matrix.at(2) == 0);
            REQUIRE(matrix.at(3) == 1);
            REQUIRE(matrix.at(4) == 2);
            REQUIRE(matrix.at(5) == 3);
        }

        SECTION("insert row") {
            Matrix<int> matrix{5, 4, 10};
            matrix.insert_row(1, {1, 1, 1, 1});
            REQUIRE_THROWS_AS( matrix.insert_row(1000, {1, 1, 1, 1}), std::out_of_range);
            REQUIRE_THROWS_AS( matrix.insert_row(3, {1, 1, 1, 1, 1, 1, 1}), std::invalid_argument);
            REQUIRE(matrix.rows() == 6);
            REQUIRE(matrix.cols() == 4);
            REQUIRE(matrix.at(4) == 1);
            REQUIRE(matrix.at(5) == 1);
            REQUIRE(matrix.at(6) == 1);
            REQUIRE(matrix.at(7) == 1);
        }

        SECTION("insert row") {
            Matrix<int> matrix{5, 4, 10};
            REQUIRE_THROWS_AS( matrix.insert_col(1000, {1, 1, 1, 1, 1}), std::out_of_range);
            REQUIRE_THROWS_AS( matrix.insert_col(3, {1, 1, 1, 1, 1, 1, 1}), std::invalid_argument);
            matrix.insert_col(1, {1, 1, 1, 1, 1});
            REQUIRE(matrix.rows() == 5);
            REQUIRE(matrix.cols() == 5);
            REQUIRE(matrix.at(1) == 1);
            REQUIRE(matrix.at(6) == 1);
            REQUIRE(matrix.at(11) == 1);
            REQUIRE(matrix.at(16) == 1);
        }

        SECTION("insert row") {
            Matrix<int> matrix{5, 4, 10};
            REQUIRE_THROWS_AS( matrix.insert_col(1000, {1, 1, 1, 1, 1}), std::out_of_range);
            REQUIRE_THROWS_AS( matrix.insert_col(3, {1, 1, 1, 1, 1, 1, 1}), std::invalid_argument);
            matrix.insert_col(1, {1, 1, 1, 1, 1});
            REQUIRE(matrix.rows() == 5);
            REQUIRE(matrix.cols() == 5);
            REQUIRE(matrix.at(1) == 1);
            REQUIRE(matrix.at(6) == 1);
            REQUIRE(matrix.at(11) == 1);
            REQUIRE(matrix.at(16) == 1);
        }

        SECTION("erase_row") {
            Matrix<int> matrix{5, 3, 10};
            matrix.erase_row(1000);
            REQUIRE(matrix.rows() == 4);
            matrix.erase_row(2);
            REQUIRE(matrix.rows() == 3);
            REQUIRE(matrix.cols() == 3);
            Matrix<int> matrix2{1, 5, 7};
            matrix2.erase_row(0);
            REQUIRE(matrix2.empty() == true);
        }

        SECTION("erase_col") {
            Matrix<int> matrix{5, 3, 10};
            matrix.erase_col(1000);
            REQUIRE(matrix.cols() == 2);
            matrix.erase_col(1);
            REQUIRE(matrix.rows() == 5);
            REQUIRE(matrix.cols() == 1);
            Matrix<int> matrix2{5, 1, 7};
            matrix2.erase_col(0);
            REQUIRE(matrix2.empty() == true);
        }

        SECTION("base operator [][]") {
            Matrix<int> matrix{5, 3, 10};
            for (size_t i = 0; i < matrix.rows(); ++i) {
                for (size_t j = 0; j < matrix.cols(); ++j) {
                    REQUIRE(matrix[i][j] == 10);
                }
            }
        }

        SECTION("const operator [][]") {
            const Matrix<int> matrix{5, 3, 10};
            for (size_t i = 0; i < matrix.rows(); ++i) {
                for (size_t j = 0; j < matrix.cols(); ++j) {
                    REQUIRE(matrix[i][j] == 10);
                }
            }
        }

        SECTION("assign by iterators") {
            Matrix<size_t> matrix{3, 4, 15};
            std::vector<size_t> vec{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
            matrix.assign(vec.begin(), vec.end());
            for (size_t j = 0; j < matrix.size(); ++j) {
                REQUIRE(matrix.at(j) == j);
            }
        }

        SECTION("assign by il") {
            Matrix<size_t> matrix{3, 4, 15};
            matrix.assign({0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30});
            for (size_t j = 0; j < matrix.size(); ++j) {
                REQUIRE(matrix.at(j) == j);
            }
        }

    }
}

TEST_CASE("Random access iterator testing") {
    SECTION("Constructors") {
        SECTION("Default constructor") {
            MatrixIterator<int, true> it{};
            REQUIRE(it.operator->() == nullptr);
        }

        SECTION("Pointer constructor") {
            int value = 42;
            MatrixIterator<int, true> it{&value};
            REQUIRE(it.operator->() == &value);
            REQUIRE(*it == 42);
        }

        SECTION("Copy constructor") {
            int value = 42;
            MatrixIterator<int, false> it{&value};
            MatrixIterator<int, true> copy_it{it};
            REQUIRE(copy_it.operator->() == &value);
            REQUIRE(*copy_it == 42);
        }
    }

    SECTION("Operator =") {
        int value1 = 14;
        int value2 = 15;
        MatrixIterator<int, false> it{&value1};
        MatrixIterator<int, true> it2{&value2};
        it2 = it;
        REQUIRE(it2.operator->() == &value1);
        REQUIRE(*it2 == value1);
    }

    SECTION("Operator []") {
        std::vector<int> vec{0, 1, 2, 3, 4};
        MatrixIterator<int, false> it{&vec[0]};

        REQUIRE(it[0] == 0);
        REQUIRE(it[2] == 2);
        REQUIRE(it[4] == 4);
    }

    SECTION("MatrixIterator increment/decrement operators") {
        std::vector<int> data = {1, 2, 3, 4, 5};
        MatrixIterator<int, false> it(&data[2]);

        SECTION("Prefix increment") {
            ++it;
            REQUIRE(*it == 4);
            REQUIRE(it.operator->() == &data[3]);
            ++it;
            REQUIRE(*it == 5);
        }

        SECTION("Postfix increment") {
            MatrixIterator<int, false> old = it++;
            REQUIRE(*old == 3);
            REQUIRE(*it == 4);
            REQUIRE(old.operator->() == &data[2]);
            REQUIRE(it.operator->() == &data[3]);
        }

        SECTION("Prefix decrement") {
            --it;
            REQUIRE(*it == 2);
            REQUIRE(it.operator->() == &data[1]);
        }

        SECTION("Postfix decrement") {
            MatrixIterator<int, false> old = it--;
            REQUIRE(*old == 3);
            REQUIRE(*it == 2);
            REQUIRE(old.operator->() == &data[2]);
            REQUIRE(it.operator->() == &data[1]);
        }
    }


    SECTION("MatrixIterator arithmetic operators") {
        std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        MatrixIterator<int, false> it(&data[5]);

        SECTION("operator+ with offset") {
            MatrixIterator<int, false> it1 = it + 2;
            REQUIRE(*it1 == 8);
            REQUIRE(it1.operator->() == &data[7]);

        }

        SECTION("operator- with offset") {
            MatrixIterator<int, false> it1 = it - 3;
            REQUIRE(*it1 == 3);
            REQUIRE(it1.operator->() == &data[2]);
        }

        SECTION("operator+= and operator-=") {
            it += 3;
            REQUIRE(*it == 9);
            REQUIRE(it.operator->() == &data[8]);

            it -= 4;
            REQUIRE(*it == 5);
            REQUIRE(it.operator->() == &data[4]);
        }

        SECTION("Difference between iterators") {
            MatrixIterator<int, false> it1(&data[2]);
            MatrixIterator<int, false> it2(&data[7]);

            REQUIRE(it2 - it1 == 5);
            REQUIRE(it1 - it2 == -5);

            MatrixIterator<int, true> const_it(&data[9]);
            REQUIRE(const_it - it1 == 7);
            REQUIRE(it1 - const_it == -7);
        }

        SECTION("Friend operator+") {
            MatrixIterator<int, false> it1 = 3 + it;
            REQUIRE(*it1 == 9);
            REQUIRE(it1.operator->() == &data[8]);
        }
    }
}


TEST_CASE("Enemy") {
    TowerDefense::ID id{123};
    std::string name{"enemy"};
    size_t gold{1000};
    float health{100};
    float max_health{100};
    float speed{120};
    TowerDefense::Point position{23, 7};
    float x_pixels{152};
    float y_pixels{150};
    auto *enemy = new TowerDefense::Enemy(id, name, gold, health, max_health, speed, position, x_pixels, y_pixels);
    SECTION("constructor") {
        REQUIRE(enemy->get_ID() == id);
        REQUIRE(enemy->get_name() == name);
        REQUIRE(enemy->get_gold() == gold);
        REQUIRE(enemy->get_health() == health);
        REQUIRE(enemy->get_max_health() == max_health);
        REQUIRE(enemy->get_speed() == speed);
        REQUIRE(enemy->get_position() == position);
        REQUIRE(enemy->get_x_pixels() == x_pixels);
        REQUIRE(enemy->get_y_pixels() == y_pixels);
    }
    SECTION("setters") {
        float x_pixels2{7};
        float y_pixels2{15};
        TowerDefense::Point position2{1, 15};
        TowerDefense::ID id2{124};
        enemy->set_x_pixels(x_pixels2);
        REQUIRE(enemy->get_x_pixels() == x_pixels2);
        enemy->set_y_pixels(y_pixels2);
        REQUIRE(enemy->get_y_pixels() == y_pixels2);
        enemy->set_position(position2);
        REQUIRE(enemy->get_position() == position2);
        enemy->set_ID(id2);
        REQUIRE(enemy->get_ID() == id2);
    }
    SECTION("take damage") {
        float damage{20.0};
        enemy->take_damage(damage);
        REQUIRE(enemy->get_health() == health - damage);
    }
    SECTION("test consts") {
        int deceleration{10};
        enemy->change_deceleration(deceleration);
        REQUIRE(enemy->get_speed() == speed * ((100 - deceleration) / 100.0));

        int weakness{10};
        float damage{20};
        enemy->change_weakness(weakness);
        enemy->take_damage(damage);
        REQUIRE(enemy->get_health() == health - damage * ((100 + weakness )/ 100.0));
    }

    SECTION("effects") {
        float magnitude{10};
        float duration{0.2};
        std::unique_ptr<TowerDefense::IEffect> poison_effect = std::make_unique<TowerDefense::PoisonEffect>(magnitude, duration);
        std::unique_ptr<TowerDefense::IEffect> weakness_effect = std::make_unique<TowerDefense::WeaknessEffect>(magnitude, duration);
        std::unique_ptr<TowerDefense::IEffect> slow_effect = std::make_unique<TowerDefense::SlowEffect>(magnitude, duration);
        enemy->add_effect(std::move(poison_effect));
        enemy->add_effect(std::move(weakness_effect));
        enemy->add_effect(std::move(slow_effect));
        float dt{0.1};
        enemy->update(dt);
        REQUIRE(enemy->get_health() == health - magnitude * ((100 + magnitude) / 100.0));
        REQUIRE(enemy->get_speed() == speed * ((100 - magnitude) / 100.0));
        enemy->update(dt);
        enemy->update(dt);
        REQUIRE(enemy->get_speed() == speed);

        std::unique_ptr<TowerDefense::IEffect> slow_effect2 = std::make_unique<TowerDefense::SlowEffect>(1000, 10);
        enemy->add_effect(std::move(slow_effect2));
        enemy->update(dt);
        REQUIRE(enemy->get_speed() == 0);

    }
    SECTION("clone") {
        std::unique_ptr<TowerDefense::IEnemy> enemy_for_copy = std::make_unique<TowerDefense::Enemy>(id, name, gold, health, max_health, speed, position, x_pixels, y_pixels);
        auto enemy2 = enemy_for_copy->clone();
        REQUIRE(enemy2->get_ID() == id);
        REQUIRE(enemy2->get_name() == name);
        REQUIRE(enemy2->get_gold() == gold);
        REQUIRE(enemy2->get_health() == health);
        REQUIRE(enemy2->get_max_health() == max_health);
        REQUIRE(enemy2->get_speed() == speed);
        REQUIRE(enemy2->get_position() == position);
        REQUIRE(enemy2->get_x_pixels() == x_pixels);
        REQUIRE(enemy2->get_y_pixels() == y_pixels);
    }
    delete enemy;
}


TEST_CASE("Effects") {
    SECTION("clone") {
        float magnitude{10.0};
        float duration{10.0};
        std::unique_ptr<TowerDefense::IEffect> poison_effect = std::make_unique<TowerDefense::PoisonEffect>(magnitude, duration);
        std::unique_ptr<TowerDefense::IEffect> weakness_effect = std::make_unique<TowerDefense::WeaknessEffect>(magnitude, duration);
        std::unique_ptr<TowerDefense::IEffect> slow_effect = std::make_unique<TowerDefense::SlowEffect>(magnitude, duration);

        auto poison_effect_copy = poison_effect->clone();
        auto weakness_effect_copy = weakness_effect->clone();
        auto slow_effect_copy = slow_effect->clone();

    }
}

TEST_CASE("Castle") {
    TowerDefense::ID id{123};
    std::string name{"castle"};
    float health{90};
    float max_health{100};
    size_t gold{10000};
    TowerDefense::Point position{100, 50};
    auto *castle = new TowerDefense::Castle(id, name, health, max_health, gold, position);
    SECTION("constructor") {
        REQUIRE(castle->get_ID() == id);
        REQUIRE(castle->get_name() == name);
        REQUIRE(castle->get_health() == health);
        REQUIRE(castle->get_max_health() == max_health);
        REQUIRE(castle->get_gold() == gold);
        REQUIRE(castle->get_position() == position);
    }
    SECTION("setters") {
        TowerDefense::ID id2{124};
        float health2{85};
        castle->set_health(health2);
        castle->set_ID(id2);
        REQUIRE(castle->get_ID() == id2);
        REQUIRE(castle->get_health() == health2);
    }
    SECTION("take damage") {
        float damage{100};
        castle->take_damage(damage);
        REQUIRE(castle->get_health() == health - damage);
    }
    SECTION("operations with gold") {
        size_t gold2{100};
        castle->add_gold(gold2);
        REQUIRE(castle->get_gold() == gold + gold2);
        castle->subtract_gold(gold2);
        REQUIRE(castle->get_gold() == gold);
    }
    delete castle;
}

TEST_CASE("Towers") {
    SECTION("Simple tower") {
        TowerDefense::ID id{542};
        float range{10.0};
        size_t level{2};
        TowerDefense::Point location{11, 14};
        std::unique_ptr<TowerDefense::IEnemyRepository> enemy_repository = std::make_unique<TowerDefense::EnemyRepository>();
        TowerDefense::IStrategy *strategy = new TowerDefense::Weakest(*enemy_repository);
        float rate_of_fire{0.5};
        float damage{10.0};
        std::unique_ptr<TowerDefense::SimpleTower> simple_tower = std::make_unique<TowerDefense::SimpleTower>(id, range, level, location, strategy, damage, rate_of_fire);
        SECTION("constructor") {
            REQUIRE(simple_tower->get_id() == id);
            REQUIRE(simple_tower->get_range() == range);
            REQUIRE(simple_tower->get_level() == level);
            REQUIRE(simple_tower->get_position() == location);
            REQUIRE(simple_tower->get_strategy() == strategy);
            REQUIRE(simple_tower->get_damage() == damage);
            REQUIRE(simple_tower->get_rate_of_fire() == rate_of_fire);
        }
        SECTION("setters") {
            TowerDefense::ID id2{552};
            float range2{11.0};
            size_t level2{3};
            TowerDefense::Point location2{15, 16};
            float rate_of_fire2{0.7};
            float damage2{12.0};

            simple_tower->set_ID(id2);
            simple_tower->set_range(range2);
            simple_tower->set_level(level2);
            simple_tower->set_position(location2);
            simple_tower->set_rate_of_fire(rate_of_fire2);
            simple_tower->set_damage(damage2);

            REQUIRE(simple_tower->get_id() == id2);
            REQUIRE(simple_tower->get_range() == range2);
            REQUIRE(simple_tower->get_level() == level2);
            REQUIRE(simple_tower->get_position() == location2);
            REQUIRE(simple_tower->get_damage() == damage2);
            REQUIRE(simple_tower->get_rate_of_fire() == rate_of_fire2);
        }

        SECTION("attack") {
            float dt{0.1};
            REQUIRE(simple_tower->try_attack(dt) ==  false);
            float dt2{2.1};
            REQUIRE(simple_tower->try_attack(dt2) ==  true);
        }

        SECTION("clone") {
            auto simple_tower2 = simple_tower->clone();
            REQUIRE(simple_tower2->get_id() == id);
            REQUIRE(simple_tower2->get_range() == range);
            REQUIRE(simple_tower2->get_level() == level);
            REQUIRE(simple_tower2->get_position() == location);
            REQUIRE(simple_tower2->get_strategy() == strategy);
            REQUIRE(dynamic_cast<TowerDefense::DamageTower &>(*simple_tower).get_damage() == damage);
            REQUIRE(simple_tower->get_rate_of_fire() == rate_of_fire);
        }
        delete strategy;
    }
    SECTION("Magic tower") {
        TowerDefense::ID id{542};
        float range{10.0};
        size_t level{2};
        TowerDefense::Point location{11, 14};
        std::unique_ptr<TowerDefense::IEnemyRepository> enemy_repository = std::make_unique<TowerDefense::EnemyRepository>();
        TowerDefense::IStrategy *strategy = new TowerDefense::Weakest(*enemy_repository);
        float rate_of_fire{0.5};
        float damage{10.0};
        std::unique_ptr<TowerDefense::IEffect> weakness_effect = std::make_unique<TowerDefense::WeaknessEffect>(10, 10);
        std::unique_ptr<TowerDefense::MagicTower> magic_tower = std::make_unique<TowerDefense::MagicTower>(id, range, level, location, strategy, damage, rate_of_fire, std::move(weakness_effect));
        SECTION("constructor") {
            REQUIRE(magic_tower->get_id() == id);
            REQUIRE(magic_tower->get_range() == range);
            REQUIRE(magic_tower->get_level() == level);
            REQUIRE(magic_tower->get_position() == location);
            REQUIRE(magic_tower->get_strategy() == strategy);
            REQUIRE(magic_tower->get_damage() == damage);
            REQUIRE(magic_tower->get_rate_of_fire() == rate_of_fire);
        }

        SECTION("clone") {
            auto magic_tower2 = magic_tower->clone();
            REQUIRE(magic_tower2->get_id() == id);
            REQUIRE(magic_tower2->get_range() == range);
            REQUIRE(magic_tower2->get_level() == level);
            REQUIRE(magic_tower2->get_position() == location);
            REQUIRE(magic_tower2->get_strategy() == strategy);
            REQUIRE(dynamic_cast<TowerDefense::DamageTower &>(*magic_tower2).get_damage() == damage);
            REQUIRE(magic_tower2->get_rate_of_fire() == rate_of_fire);
        }
        delete strategy;
    }

    SECTION("Magic trap") {
        TowerDefense::ID id{512};
        float range{15.0};
        size_t level{1};
        TowerDefense::Point location{10, 11};
        std::unique_ptr<TowerDefense::IEnemyRepository> enemy_repository = std::make_unique<TowerDefense::EnemyRepository>();
        TowerDefense::IStrategy *strategy = new TowerDefense::Strongest(*enemy_repository);
        float rate_of_fire{0.5};
        std::unique_ptr<TowerDefense::IEffect> weakness_effect = std::make_unique<TowerDefense::WeaknessEffect>(10, 10);
        std::unique_ptr<TowerDefense::MagicTrap> magic_trap = std::make_unique<TowerDefense::MagicTrap>(id, range, level, location, strategy, rate_of_fire, std::move(weakness_effect));

        SECTION("constructor") {
            REQUIRE(magic_trap->get_id() == id);
            REQUIRE(magic_trap->get_range() == range);
            REQUIRE(magic_trap->get_level() == level);
            REQUIRE(magic_trap->get_position() == location);
            REQUIRE(magic_trap->get_strategy() == strategy);
            REQUIRE(magic_trap->get_rate_of_fire() == rate_of_fire);
        }

        SECTION("clone") {
            auto magic_trap2 = magic_trap->clone();
            REQUIRE(magic_trap2->get_id() == id);
            REQUIRE(magic_trap2->get_range() == range);
            REQUIRE(magic_trap2->get_level() == level);
            REQUIRE(magic_trap2->get_position() == location);
            REQUIRE(magic_trap2->get_strategy() == strategy);
            REQUIRE(magic_trap2->get_rate_of_fire() == rate_of_fire);
        }
        delete strategy;
    }
}

TEST_CASE("Visitors") {
    SECTION("Attack visitor") {
        float range{10.0};
        size_t level{2};
        TowerDefense::Point location{1, 2};
        std::unique_ptr<TowerDefense::IEnemyRepository> enemy_repository = std::make_unique<TowerDefense::EnemyRepository>();
        TowerDefense::IStrategy *strategy = new TowerDefense::Weakest(*enemy_repository);
        TowerDefense::IStrategy *all_in_range = new TowerDefense::AllInRange(*enemy_repository);
        float rate_of_fire{0.5};
        float damage{10.0};
        std::unique_ptr<TowerDefense::IEffect> slow_effect = std::make_unique<TowerDefense::SlowEffect>(10, 10);

        std::unique_ptr<TowerDefense::SimpleTower> simple_tower = std::make_unique<TowerDefense::SimpleTower>(1, range, level, location, strategy, damage, rate_of_fire);
        std::unique_ptr<TowerDefense::MagicTower> magic_tower = std::make_unique<TowerDefense::MagicTower>(2, range, level, location, strategy, damage, rate_of_fire, slow_effect->clone());
        std::unique_ptr<TowerDefense::MagicTrap> magic_trap = std::make_unique<TowerDefense::MagicTrap>(3, range, level, location, all_in_range, rate_of_fire, slow_effect->clone());

        std::unique_ptr<TowerDefense::IAttackVisitor> simple_tower_attack_visitor = std::make_unique<TowerDefense::SimpleTowerAttackVisitor>();
        std::unique_ptr<TowerDefense::IAttackVisitor> magic_tower_attack_visitor = std::make_unique<TowerDefense::MagicTowerAttackVisitor>();
        std::unique_ptr<TowerDefense::IAttackVisitor> magic_trap_attack_visitor = std::make_unique<TowerDefense::MagicTrapAttackVisitor>();

        float dt(0.1);
        SECTION("empty repository of enemies") {
            auto attack_info1 = simple_tower->accept_attack_visitor(*simple_tower_attack_visitor, dt);
            auto attack_info2 = magic_tower->accept_attack_visitor(*magic_tower_attack_visitor, dt);
            auto attack_info3 = magic_trap->accept_attack_visitor(*magic_trap_attack_visitor, dt);
            TowerDefense::AttackInfo info{};
            REQUIRE(attack_info1 == info);
            REQUIRE(attack_info2 == info);
            REQUIRE(attack_info3 == info);
        }

        SECTION("Filled repository of enemies") {
            std::unique_ptr<TowerDefense::IEnemy> enemy1 = std::make_unique<TowerDefense::Enemy>(11, "name", 1000, 100.0, 150.0, 100, TowerDefense::Point{0, 0}, 32.0, 32.0);
            std::unique_ptr<TowerDefense::IEnemy> enemy2 = std::make_unique<TowerDefense::Enemy>(12, "name", 1000, 90.0, 150.0, 100, TowerDefense::Point{0, 0}, 32.0, 32.0);
            std::unique_ptr<TowerDefense::IEnemy> enemy3 = std::make_unique<TowerDefense::Enemy>(13, "name", 1000, 80.0, 150.0, 100, TowerDefense::Point{0, 0}, 32.0, 32.0);
            std::unique_ptr<TowerDefense::IEnemy> enemy4 = std::make_unique<TowerDefense::Enemy>(14, "name", 1000, 70.0, 150.0, 100, TowerDefense::Point{0, 0}, 32.0, 32.0);

            enemy_repository->add_enemy(std::move(enemy1));
            enemy_repository->add_enemy(std::move(enemy2));
            enemy_repository->add_enemy(std::move(enemy3));
            enemy_repository->add_enemy(std::move(enemy4));

            auto attack_info1 = simple_tower->accept_attack_visitor(*simple_tower_attack_visitor, dt);
            REQUIRE(attack_info1.enemy_id == 0);
            auto attack_info2 = simple_tower->accept_attack_visitor(*simple_tower_attack_visitor, 2.0);
            REQUIRE(attack_info2.enemy_id == 14);
            REQUIRE(enemy_repository->get(14)->get_health() == 70 - damage);

            auto attack_info3 = magic_tower->accept_attack_visitor(*magic_tower_attack_visitor, 2.0);
            REQUIRE(attack_info3.enemy_id == 14);
            REQUIRE(enemy_repository->get(14)->get_health() == 70 - damage * 2);
            REQUIRE(enemy_repository->get(14)->get_speed() == 100 * 0.9);

            auto attack_info4 = magic_trap->accept_attack_visitor(*magic_trap_attack_visitor, 2.0);
            REQUIRE(enemy_repository->get(14)->get_speed() == 100 * 0.8);
            REQUIRE(enemy_repository->get(13)->get_speed() == 100 * 0.9);
            REQUIRE(enemy_repository->get(12)->get_speed() == 100 * 0.9);
            REQUIRE(enemy_repository->get(11)->get_speed() == 100 * 0.9);
        }
        delete strategy;
        delete all_in_range;
    }

    SECTION("Upgrade visitor") {
        float range{15.0};
        size_t level{1};
        TowerDefense::Point location{1, 2};
        std::unique_ptr<TowerDefense::IEnemyRepository> enemy_repository = std::make_unique<TowerDefense::EnemyRepository>();
        TowerDefense::IStrategy *strategy = new TowerDefense::Weakest(*enemy_repository);
        TowerDefense::IStrategy *all_in_range = new TowerDefense::AllInRange(*enemy_repository);
        float rate_of_fire{0.5};
        float damage{10.0};
        std::unique_ptr<TowerDefense::IEffect> poison_effect = std::make_unique<TowerDefense::PoisonEffect>(10, 10);

        std::unique_ptr<TowerDefense::SimpleTower> simple_tower = std::make_unique<TowerDefense::SimpleTower>(1, range, level, location, strategy, damage, rate_of_fire);
        std::unique_ptr<TowerDefense::MagicTower> magic_tower = std::make_unique<TowerDefense::MagicTower>(2, range, level, location, strategy, damage, rate_of_fire, poison_effect->clone());
        std::unique_ptr<TowerDefense::MagicTrap> magic_trap = std::make_unique<TowerDefense::MagicTrap>(3, range, level, location, all_in_range, rate_of_fire, poison_effect->clone());

        std::unique_ptr<TowerDefense::IUpgradeVisitor> simple_tower_upgrade_visitor = std::make_unique<TowerDefense::SimpleTowerUpgradeVisitor>();
        std::unique_ptr<TowerDefense::IUpgradeVisitor> magic_tower_upgrade_visitor = std::make_unique<TowerDefense::MagicTowerUpgradeVisitor>();
        std::unique_ptr<TowerDefense::IUpgradeVisitor> magic_trap_upgrade_visitor = std::make_unique<TowerDefense::MagicTrapUpgradeVisitor>();

        TowerDefense::LevelDTO dto{2, 1000, 15.0,{{"damage", 20.0 }, {"rate_of_fire", 1.0}}};

        simple_tower->accept_upgrade_visitor(*simple_tower_upgrade_visitor, dto);
        magic_tower->accept_upgrade_visitor(*magic_tower_upgrade_visitor, dto);
        magic_trap->accept_upgrade_visitor(*magic_trap_upgrade_visitor, dto);

        REQUIRE(simple_tower->get_rate_of_fire() == 1.0);
        REQUIRE(magic_tower->get_rate_of_fire() == 1.0);
        REQUIRE(magic_trap->get_rate_of_fire() == 1.0);
        REQUIRE(simple_tower->get_damage() == 20.0);
        REQUIRE(magic_tower->get_damage() == 20.0);

        delete strategy;
        delete all_in_range;
    }
}


TEST_CASE("Strategy") {
    auto enemy_repository = std::make_unique<TowerDefense::EnemyRepository>();

    std::unique_ptr<TowerDefense::IEnemy> enemy1 = std::make_unique<TowerDefense::Enemy>(1, "name", 100, 100.0, 150.0, 100, TowerDefense::Point{1, 0}, 0.0, 0.0);
    std::unique_ptr<TowerDefense::IEnemy> enemy2 = std::make_unique<TowerDefense::Enemy>(2, "name", 100, 95.0, 150.0, 100, TowerDefense::Point{0, 2}, 0.0, 0.0);
    std::unique_ptr<TowerDefense::IEnemy> enemy3 = std::make_unique<TowerDefense::Enemy>(3, "name", 100, 20.0, 150.0, 100, TowerDefense::Point{3, 7}, 0.0, 0.0);
    std::unique_ptr<TowerDefense::IEnemy> enemy4 = std::make_unique<TowerDefense::Enemy>(4, "name", 100, 75.0, 150.0, 100, TowerDefense::Point{1, 2}, 0.0, 0.0);
    enemy_repository->add_enemy(std::move(enemy1));
    enemy_repository->add_enemy(std::move(enemy2));
    enemy_repository->add_enemy(std::move(enemy3));
    enemy_repository->add_enemy(std::move(enemy4));

    auto castle_repository = std::make_unique<TowerDefense::CastleRepository>();

    std::unique_ptr<TowerDefense::ICastle> castle = std::make_unique<TowerDefense::Castle>(100, "name", 1000, 1000, 15000, TowerDefense::Point{15, 4});
    castle_repository->add_castle(std::move(castle));
    SECTION("All in range") {
        auto all_in_range = std::make_unique<TowerDefense::AllInRange>(*enemy_repository);
        auto res = all_in_range->find_target(4.0f, TowerDefense::Point(0,0));
        for (auto enemy : res) {
            REQUIRE(enemy->get_ID() != 3);
        }
    }
    SECTION("Weakest") {
        auto weakest = std::make_unique<TowerDefense::Weakest>(*enemy_repository);
        auto res = weakest->find_target(4.0f, TowerDefense::Point(0,0));
        for (auto enemy : res) {
            REQUIRE(enemy->get_ID() == 4);
        }
    }
    SECTION("Strongest") {
        auto strongest = std::make_unique<TowerDefense::Strongest>(*enemy_repository);
        auto res = strongest->find_target(4.0f, TowerDefense::Point(0,0));
        for (auto enemy : res) {
            REQUIRE(enemy->get_ID() == 1);
        }
    }
    SECTION("Nearest to tower") {
        auto nearest_to_tower = std::make_unique<TowerDefense::NearestToTower>(*enemy_repository);
        auto res = nearest_to_tower->find_target(15.0f, TowerDefense::Point(2,0));
        for (auto enemy : res) {
            REQUIRE(enemy->get_ID() == 2);
        }
    }
    SECTION("Nearest to castle") {
        auto nearest_to_castle = std::make_unique<TowerDefense::NearestToCastle>(*enemy_repository, *castle_repository);
        auto res = nearest_to_castle->find_target(15.0f, TowerDefense::Point(0,2));
        for (auto enemy : res) {
            REQUIRE(enemy->get_ID() == 3);
        }
    }
}

TEST_CASE("Service") {
    SECTION("Economy service") {

        auto castle_repository = std::make_unique<TowerDefense::CastleRepository>();
        auto castle = std::make_unique<TowerDefense::Castle>(123, "castle", 10000, 10000, 5000, TowerDefense::Point(1, 1));
        castle_repository->add_castle(std::move(castle));

        std::unique_ptr<TowerDefense::IEnemyRepository> enemy_repository = std::make_unique<TowerDefense::EnemyRepository>();
        TowerDefense::IStrategy *strategy = new TowerDefense::Weakest(*enemy_repository);

        auto tower_repository = std::make_unique<TowerDefense::TowerRepository>();
        auto simple_tower1 = std::make_unique<TowerDefense::SimpleTower>(1, 12.3, 1, TowerDefense::Point(8, 2), strategy, 10, 0.2);
        auto simple_tower2 = std::make_unique<TowerDefense::SimpleTower>(2, 12.3, 2, TowerDefense::Point(8, 2), strategy, 10, 0.2);
        tower_repository->add_tower(std::move(simple_tower1));
        tower_repository->add_tower(std::move(simple_tower2));



        std::vector<TowerDefense::LevelDTO> simple_tower_levels = {
            {1, 1000, 13.5, {{"rate_of_fire", 0.5}, {"damage", 10.0}}},
            {2, 2000, 15.5, {{"rate_of_fire", 0.7}, {"damage", 15.0}}}
        };

        std::vector<TowerDefense::LevelDTO> magic_tower_levels = {
            {1, 1000, 13.5, {{"rate_of_fire", 0.5}, {"damage", 10.0}}},
            {2, 2000, 15.5, {{"rate_of_fire", 0.7}, {"damage", 15.0}}}
        };


        std::vector<TowerDefense::LevelDTO> magic_trap_levels = {
            {1, 1000, 13.5, {{"rate_of_fire", 0.5}}},
            {2, 2000, 15.5, {{"rate_of_fire", 0.7}}}
        };


        TowerDefense::LevelConfig conf = {
            .levels = {{"simple_tower", simple_tower_levels}, {"magic_tower", magic_tower_levels}, {"magic_trap", magic_trap_levels}}
        };


        auto economy_service_ = std::make_unique<TowerDefense::EconomyService>(*tower_repository, *castle_repository, conf);
        economy_service_->add_visitor(typeid(TowerDefense::SimpleTower), std::make_unique<TowerDefense::SimpleTowerUpgradeVisitor>());
        economy_service_->add_visitor(typeid(TowerDefense::MagicTower), std::make_unique<TowerDefense::MagicTowerUpgradeVisitor>());


        REQUIRE(economy_service_->upgrade(1) == true);
        REQUIRE(tower_repository->get(1)->get_range() == 15.5f);
        REQUIRE(tower_repository->get(1)->get_rate_of_fire() == 0.7f);
        REQUIRE(economy_service_->upgrade(1) == false);

        delete strategy;
    }

    SECTION("Enemy service") {
        auto enemy_repository = std::make_unique<TowerDefense::EnemyRepository>();

        std::unique_ptr<TowerDefense::IEnemy> enemy1 = std::make_unique<TowerDefense::Enemy>(1, "name", 100, 100.0, 150.0, 100, TowerDefense::Point{1, 0}, 0.0, 0.0);
        std::unique_ptr<TowerDefense::IEnemy> enemy2 = std::make_unique<TowerDefense::Enemy>(2, "name", 100, 95.0, 150.0, 100, TowerDefense::Point{0, 2}, 0.0, 0.0);
        std::unique_ptr<TowerDefense::IEnemy> enemy3 = std::make_unique<TowerDefense::Enemy>(3, "name", 100, 20.0, 150.0, 100, TowerDefense::Point{7, 3}, 0.0, 0.0);
        std::unique_ptr<TowerDefense::IEnemy> enemy4 = std::make_unique<TowerDefense::Enemy>(4, "name", 100, 75.0, 150.0, 100, TowerDefense::Point{1, 2}, 0.0, 0.0);

        enemy_repository->add_enemy(std::move(enemy1));
        enemy_repository->add_enemy(std::move(enemy2));
        enemy_repository->add_enemy(std::move(enemy3));
        enemy_repository->add_enemy(std::move(enemy4));

        auto castle_repository = std::make_unique<TowerDefense::CastleRepository>();

        std::unique_ptr<TowerDefense::ICastle> castle = std::make_unique<TowerDefense::Castle>(100, "name", 1000, 1000, 15000, TowerDefense::Point{7, 3});
        castle_repository->add_castle(std::move(castle));

        auto enemy_service = std::make_unique<TowerDefense::EnemyService>(*castle_repository, *enemy_repository);
        enemy_service->attack_all();

        REQUIRE(castle_repository->get()->get_health() == 1000 - 20);
        REQUIRE_THROWS_AS(enemy_repository->get(3), std::out_of_range);

        std::unique_ptr<TowerDefense::IEnemy> enemy5 = std::make_unique<TowerDefense::Enemy>(5, "name", 100, 100000.0, 150.0, 100, TowerDefense::Point{7, 3}, 0.0, 0.0);
        enemy_repository->add_enemy(std::move(enemy5));
        enemy_service->attack_all();
        REQUIRE(castle_repository->get()->get_health() == 0);
    }
    SECTION("Tower service seq") {
        auto enemy1 = std::make_unique<TowerDefense::Enemy>(1, "name", 100, 100.0, 150.0, 100, TowerDefense::Point{1, 0}, 0.0, 0.0);
        auto enemy2 = std::make_unique<TowerDefense::Enemy>(2, "name", 100, 95.0, 150.0, 100, TowerDefense::Point{0, 2}, 0.0, 0.0);
        auto enemy3 = std::make_unique<TowerDefense::Enemy>(3, "name", 100, 20.0, 150.0, 100, TowerDefense::Point{7, 2}, 0.0, 0.0);
        auto enemy4 = std::make_unique<TowerDefense::Enemy>(4, "name", 100, 75.0, 150.0, 100, TowerDefense::Point{1, 2}, 0.0, 0.0);
        auto enemy_repository = std::make_unique<TowerDefense::EnemyRepository>();
        auto castle_repository = std::make_unique<TowerDefense::CastleRepository>();
        auto castle = std::make_unique<TowerDefense::Castle>(6, "castle", 100.0, 100.0, 10000, TowerDefense::Point{0, 0});
        castle_repository->add_castle(std::move(castle));

        enemy_repository->add_enemy(std::move(enemy1));
        enemy_repository->add_enemy(std::move(enemy2));
        enemy_repository->add_enemy(std::move(enemy3));
        enemy_repository->add_enemy(std::move(enemy4));

        auto strategy = std::make_unique<TowerDefense::NearestToTower>(*enemy_repository);

        auto tower = std::make_unique<TowerDefense::SimpleTower>(5, 12.3, 1, TowerDefense::Point(2, 7), strategy.get(), 10, 1);
        auto tower_repository = std::make_unique<TowerDefense::TowerRepository>();
        tower_repository->add_tower(std::move(tower));
        auto tower_service = std::make_unique<TowerDefense::TowerService>(*tower_repository, *enemy_repository, *castle_repository);
        auto visitor = std::make_unique<TowerDefense::SimpleTowerAttackVisitor>();
        tower_service->add_visitor(typeid(TowerDefense::SimpleTower), std::move(visitor));
        auto info = tower_service->attack_all(2);
        REQUIRE(info[0].enemy_id == 3);
        REQUIRE(info[0].tower_id == 5);
        REQUIRE(info[0].tower_type == "simple_tower");
        REQUIRE(enemy_repository->get(3)->get_health() == 10);
        info = tower_service->attack_all(2);
        REQUIRE_THROWS_AS(enemy_repository->get(3), std::out_of_range);
    }

    SECTION("Tower service par") {
        auto enemy1 = std::make_unique<TowerDefense::Enemy>(1, "name", 100, 100.0, 150.0, 100, TowerDefense::Point{1, 0}, 0.0, 0.0);
        auto enemy2 = std::make_unique<TowerDefense::Enemy>(2, "name", 100, 95.0, 150.0, 100, TowerDefense::Point{0, 2}, 0.0, 0.0);
        auto enemy3 = std::make_unique<TowerDefense::Enemy>(3, "name", 100, 20.0, 150.0, 100, TowerDefense::Point{7, 2}, 0.0, 0.0);
        auto enemy4 = std::make_unique<TowerDefense::Enemy>(4, "name", 100, 75.0, 150.0, 100, TowerDefense::Point{1, 2}, 0.0, 0.0);
        auto enemy_repository = std::make_unique<TowerDefense::EnemyRepository>();
        auto castle_repository = std::make_unique<TowerDefense::CastleRepository>();
        auto castle = std::make_unique<TowerDefense::Castle>(6, "castle", 100.0, 100.0, 10000, TowerDefense::Point{0, 0});
        castle_repository->add_castle(std::move(castle));

        enemy_repository->add_enemy(std::move(enemy1));
        enemy_repository->add_enemy(std::move(enemy2));
        enemy_repository->add_enemy(std::move(enemy3));
        enemy_repository->add_enemy(std::move(enemy4));

        auto strategy = std::make_unique<TowerDefense::NearestToTower>(*enemy_repository);
        auto tower_repository = std::make_unique<TowerDefense::TowerRepository>();
        for (size_t i = 20; i < 100; ++i) {
            auto tower = std::make_unique<TowerDefense::SimpleTower>(i, 1.1, 1, TowerDefense::Point(2, 7), strategy.get(), 10, 1);
            tower_repository->add_tower(std::move(tower));
        }
        auto tower_service = std::make_unique<TowerDefense::TowerService>(*tower_repository, *enemy_repository, *castle_repository);
        auto visitor = std::make_unique<TowerDefense::SimpleTowerAttackVisitor>();
        tower_service->add_visitor(typeid(TowerDefense::SimpleTower), std::move(visitor));
        auto info = tower_service->attack_all_par(2);
        REQUIRE_THROWS_AS(enemy_repository->get(3), std::out_of_range);
    }
    SECTION("Move service seq") {
        auto game_filed = std::make_unique<TowerDefense::GameFiled>(3, 3);
        TowerDefense::Cell cell_road;
        cell_road.landscape_type = "road";
        TowerDefense::Cell cell_grass;
        cell_grass.landscape_type = "grass";
        game_filed->set_cell(0, 0, cell_road);
        game_filed->set_cell(0, 1, cell_road);
        game_filed->set_cell(0, 2, cell_grass);
        game_filed->set_cell(1, 0, cell_grass);
        game_filed->set_cell(1, 1, cell_road);
        game_filed->set_cell(1, 2, cell_grass);
        game_filed->set_cell(2, 0, cell_grass);
        game_filed->set_cell(2, 1, cell_road);
        game_filed->set_cell(2, 2, cell_road);
        auto enemy1 = std::make_unique<TowerDefense::Enemy>(1, "name", 100, 100.0, 150.0, 10, TowerDefense::Point{0, 0}, 32, 32);
        auto enemy_repository = std::make_unique<TowerDefense::EnemyRepository>();
        enemy_repository->add_enemy(std::move(enemy1));
        auto move_service = std::make_unique<TowerDefense::MoveService>(*enemy_repository, *game_filed);
        move_service->move(2);
        REQUIRE(enemy_repository->get(1)->get_position().x_ == 0);
        REQUIRE(enemy_repository->get(1)->get_position().y_ == 0);
        move_service->move(2);
        REQUIRE(enemy_repository->get(1)->get_position().x_ == 1);
        REQUIRE(enemy_repository->get(1)->get_position().y_ == 0);
    }

    SECTION("ID service") {
        auto id_service = std::make_unique<TowerDefense::ID_service>(123);
        REQUIRE(id_service->get_id() == 124);
        id_service->set_id(100);
        REQUIRE(id_service->get_id() == 101);
    }
    SECTION("Move service seq") {
        auto game_filed = std::make_unique<TowerDefense::GameFiled>(3, 3);
        TowerDefense::Cell cell_road;
        cell_road.landscape_type = "road";
        TowerDefense::Cell cell_grass;
        cell_grass.landscape_type = "grass";
        game_filed->set_cell(0, 0, cell_road);
        game_filed->set_cell(0, 1, cell_road);
        game_filed->set_cell(0, 2, cell_grass);
        game_filed->set_cell(1, 0, cell_grass);
        game_filed->set_cell(1, 1, cell_road);
        game_filed->set_cell(1, 2, cell_grass);
        game_filed->set_cell(2, 0, cell_grass);
        game_filed->set_cell(2, 1, cell_road);
        game_filed->set_cell(2, 2, cell_road);
        auto enemy_repository = std::make_unique<TowerDefense::EnemyRepository>();
        for (size_t i = 1; i < 50; ++i) {
            auto enemy = std::make_unique<TowerDefense::Enemy>(i, "name", 100, 100.0, 150.0, 10, TowerDefense::Point{0, 0}, 32, 32);
            enemy_repository->add_enemy(std::move(enemy));
        }

        auto move_service = std::make_unique<TowerDefense::MoveService>(*enemy_repository, *game_filed);
        move_service->move_par(2);
        REQUIRE(enemy_repository->get(1)->get_position().x_ == 0);
        REQUIRE(enemy_repository->get(1)->get_position().y_ == 0);
        move_service->move_par(2);
        REQUIRE(enemy_repository->get(1)->get_position().x_ == 1);
        REQUIRE(enemy_repository->get(1)->get_position().y_ == 0);
    }
    SECTION("State service") {
        auto strategy_repository = std::make_unique<TowerDefense::StrategyRepository>();
        auto mapper_repository = std::make_unique<TowerDefense::MapperRepository>();
        auto castle_dto_mapper = std::make_unique<TowerDefense::CastleDTOMapper>();
        auto castle_mapper = std::make_unique<TowerDefense::CastleMapper>();
        auto enemy_dto_mapper = std::make_unique<TowerDefense::EnemyDTOMapper>();
        auto enemy_mapper = std::make_unique<TowerDefense::EnemyMapper>();
        auto tower_dto_mapper = std::make_unique<TowerDefense::SimpleTowerDTOMapper>(*strategy_repository);
        auto tower_mapper = std::make_unique<TowerDefense::SimpleTowerMapper>(*strategy_repository);
        mapper_repository->add_castle_dto_mapper(std::move(castle_dto_mapper));
        mapper_repository->add_castle_mapper(std::move(castle_mapper));
        mapper_repository->add_enemy_dto_mapper(std::move(enemy_dto_mapper));
        mapper_repository->add_enemy_mapper(std::move(enemy_mapper));
        mapper_repository->add_tower_mapper("simple_tower", std::move(tower_mapper));
        mapper_repository->add_tower_dto_mapper(typeid(TowerDefense::SimpleTower), std::move(tower_dto_mapper));

        auto enemy_repository = std::make_unique<TowerDefense::EnemyRepository>();
        auto enemy = std::make_unique<TowerDefense::Enemy>(123, "enemy", 100, 150, 200, 120, TowerDefense::Point(4, 3), 33, 32);
        enemy_repository->add_enemy(std::move(enemy));
        auto tower_repository = std::make_unique<TowerDefense::TowerRepository>();
        auto castle_repository = std::make_unique<TowerDefense::CastleRepository>();
        auto castle = std::make_unique<TowerDefense::Castle>(1, "castle", 1000, 2000, 150, TowerDefense::Point(5, 7));
        castle_repository->add_castle(std::move(castle));

        auto state_service = std::make_unique<TowerDefense::YamlStateService>(*castle_repository, *enemy_repository, *tower_repository, *mapper_repository);
        state_service->save_castle("../../save_load/castle.yaml");
        state_service->load_castle("../../save_load/castle.yaml");
        REQUIRE(castle_repository->get()->get_ID() == 1);
        REQUIRE(castle_repository->get()->get_health() == 1000);
        REQUIRE(castle_repository->get()->get_max_health() == 2000);
        REQUIRE(castle_repository->get()->get_gold() == 150);
        REQUIRE(castle_repository->get()->get_position() == TowerDefense::Point(5, 7));


        state_service->save_enemy("../../save_load/enemy.yaml");
        enemy_repository->reset();
        state_service->load_enemy("../../save_load/enemy.yaml");
        REQUIRE(enemy_repository->get(123)->get_ID() == 123);
        REQUIRE(enemy_repository->get(123)->get_health() == 150);
        REQUIRE(enemy_repository->get(123)->get_max_health() == 200);
        REQUIRE(enemy_repository->get(123)->get_gold() == 100);
        REQUIRE(enemy_repository->get(123)->get_position() == TowerDefense::Point(4, 3));


        auto strategy = std::make_unique<TowerDefense::Weakest>(*enemy_repository);
        auto tower = std::make_unique<TowerDefense::SimpleTower>(2, 1.1, 1, TowerDefense::Point(2, 7), strategy.get(), 10, 1);
        tower_repository->add_tower(std::move(tower));
        strategy_repository->add_strategy("weakest", std::move(strategy));

        state_service->save_tower("../../save_load/tower.yaml");
        tower_repository->reset();
        state_service->load_tower("../../save_load/tower.yaml");
        REQUIRE(tower_repository->get(2)->get_id() == 2);
        REQUIRE(tower_repository->get(2)->get_range() == 1.1f);
        REQUIRE(tower_repository->get(2)->get_level() == 1);
        REQUIRE(tower_repository->get(2)->get_position() == TowerDefense::Point(2, 7));
    }
}

TEST_CASE("Game field") {
    TowerDefense::GameFiled game_field(6, 5);
    REQUIRE(game_field.get_width() == 6);
    REQUIRE(game_field.get_height() == 5);
    TowerDefense::Cell cell{"grass"};
    game_field.set_cell(1, 4, cell);
    REQUIRE(game_field.get_cell(1, 4).landscape_type == "grass");
}


TEST_CASE("Factory") {
    std::unique_ptr<TowerDefense::IID_service> id_service = std::make_unique<TowerDefense::ID_service>();
    SECTION("Castle factory") {
        TowerDefense::CastleDTO castle_dto {1,"castle",1000,2500,1000,15,8};
        auto castle_factory = std::make_unique<TowerDefense::CastleFactory>(*id_service, castle_dto);
        auto castle = castle_factory->create_castle();
        REQUIRE(castle->get_name() == "castle");
        REQUIRE(castle->get_health() == 1000);
        REQUIRE(castle->get_max_health() == 2500);
        REQUIRE(castle->get_gold() == 1000);
        REQUIRE(castle->get_position() == TowerDefense::Point{15, 8});
    }
    SECTION("Effect factory") {
        TowerDefense::EffectConfig conf{
            {{"slow", 10, 10}, {"poison", 20, 10}, {"weakness", 10, 20}}
        };
        auto effect_factory = std::make_unique<TowerDefense::EffectFactory>(conf);
        std::unique_ptr<TowerDefense::IEffect> slow_effect = std::make_unique<TowerDefense::SlowEffect>(10, 10);
        auto slow_effect_created = effect_factory->create_effect("slow");
        REQUIRE(effect_factory->get_effect_name(slow_effect.get()) == "slow");
        REQUIRE(effect_factory->get_effect_name(slow_effect_created.get()) == "slow");
    }
    SECTION("Enemy factory") {
        TowerDefense::EnemyDTO enemy_dto {1,"enemy",100,500,100,120,8, 9, 64, 32};
        auto enemy_factory = std::make_unique<TowerDefense::EnemyFactory>(*id_service, enemy_dto);
        auto enemy = enemy_factory->create_enemy();
        REQUIRE(enemy->get_name() == "enemy");
        REQUIRE(enemy->get_health() == 100);
        REQUIRE(enemy->get_max_health() == 500);
        REQUIRE(enemy->get_gold() == 100);
        REQUIRE(enemy->get_speed() == 120);
        REQUIRE(enemy->get_position() == TowerDefense::Point{8, 9});
        REQUIRE(enemy->get_x_pixels() == 64);
        REQUIRE(enemy->get_y_pixels() == 32);
    }
    SECTION("Tower factory") {
        TowerDefense::TowerDTO simple_tower_dto1{ 1, "simple_tower_nearest_to_tower_strategy",4.0, 1, 0, 0, 800, "nearest_to_tower", {{"damage", "10.0"}, {"rate_of_fire", "4.2"}}};
        TowerDefense::TowerDTO simple_tower_dto2{ 1, "simplee_tower_nearest_to_tower_strategy",4.0, 1, 0, 0, 100000, "nearest_to_tower", {{"damage", "10.0"}, {"rate_of_fire", "4.2"}}};
        TowerDefense::TowerDTO magic_tower_dto{ 1, "magic_tower",4.0, 1, 0, 0, 800, "nearest_to_tower", {{"damage", "10.0"}, {"rate_of_fire", "4.2"}, {"effect", "slow"}}};
        TowerDefense::TowerDTO magic_trap_dto{ 1, "magic_trap",4.0, 1, 0, 0, 800, "nearest_to_tower", {{"rate_of_fire", "4.2"}, {"effect", "slow"}}};
        TowerDefense::TowerConfig tower_conf {
            .towers = {{"simple_tower", {simple_tower_dto1, simple_tower_dto2}}, {"magic_tower", {magic_tower_dto}}, {"magic_trap", {magic_trap_dto}}}
        };

        auto enemy_repository = std::make_unique<TowerDefense::EnemyRepository>();

        auto strategy_repository = std::make_unique<TowerDefense::StrategyRepository>();
        strategy_repository->add_strategy("nearest_to_tower", std::make_unique<TowerDefense::NearestToTower>(*enemy_repository));

        auto castle_repository = std::make_unique<TowerDefense::CastleRepository>();
        auto castle = std::make_unique<TowerDefense::Castle>(123, "castle", 10000, 10000, 5000, TowerDefense::Point(1, 1));
        castle_repository->add_castle(std::move(castle));

        TowerDefense::EffectConfig effect_conf {{{"slow", 10, 10}, {"poison", 20, 10}, {"weakness", 10, 20}}};
        auto effect_factory = std::make_unique<TowerDefense::EffectFactory>(effect_conf);


        auto tower_factory = std::make_unique<TowerDefense::TowerFactory>(*effect_factory, *strategy_repository, *castle_repository, *id_service, tower_conf);

        auto tower = tower_factory->create_tower("simple_tower_nearest_to_tower_strategy", TowerDefense::Point(1, 2));

        REQUIRE(tower->get_position() == TowerDefense::Point(1, 2));
        REQUIRE(tower->get_rate_of_fire() == 4.2f);
        REQUIRE(tower->get_range() == 4.0f);
        REQUIRE(tower->get_level() == 1);

        auto tower2 = tower_factory->create_tower("simplee_tower_nearest_to_tower_strategy", TowerDefense::Point(1, 2));
        REQUIRE(tower2 == nullptr);
    }
}

TEST_CASE("Repository") {
    SECTION("Castle repository") {
        auto castle_repository = std::make_unique<TowerDefense::CastleRepository>();
        auto castle = std::make_unique<TowerDefense::Castle>(123, "castle", 10000, 11000, 5000, TowerDefense::Point(1, 1));
        castle_repository->add_castle(std::move(castle));
        auto castle2 = castle_repository->get();
        REQUIRE(castle2->get_ID() == 123);
        REQUIRE(castle2->get_name() == "castle");
        REQUIRE(castle2->get_health() == 10000);
        REQUIRE(castle2->get_max_health() == 11000);
        REQUIRE(castle2->get_position() == TowerDefense::Point(1, 1));
        castle.reset();
    }
    SECTION("Enemy repository") {
        auto enemy_repository = std::make_unique<TowerDefense::EnemyRepository>();
        auto enemy1 = std::make_unique<TowerDefense::Enemy>(123, "enemy", 100, 150, 100, 120, TowerDefense::Point(1, 1), 32, 32);
        auto enemy2 = std::make_unique<TowerDefense::Enemy>(124, "enemy", 100, 150, 100, 120, TowerDefense::Point(2, 3), 32, 32);
        enemy_repository->add_enemy(std::move(enemy1));
        enemy_repository->add_enemy(std::move(enemy2));
        REQUIRE(enemy_repository->get(123)->get_ID() == 123);
        REQUIRE(enemy_repository->get_all().size() == 2);
        enemy_repository->delete_enemy(123);
        REQUIRE_THROWS_AS(enemy_repository->get(123), std::out_of_range);
        enemy_repository->reset();
        REQUIRE(enemy_repository->get_all().empty());
    }

    SECTION("Strategy repository") {
        auto enemy_repository = std::make_unique<TowerDefense::EnemyRepository>();
        auto strategy_repository = std::make_unique<TowerDefense::StrategyRepository>();
        auto nearest_to_tower = std::make_unique<TowerDefense::NearestToTower>(*enemy_repository);
        strategy_repository->add_strategy("nearest_to_tower", std::move(nearest_to_tower));
        auto strategy = strategy_repository->get_strategy("nearest_to_tower");
        REQUIRE(strategy_repository->get_strategy_name(strategy) == "nearest_to_tower");
    }
    SECTION("Tower repository") {

        auto enemy_repository = std::make_unique<TowerDefense::EnemyRepository>();
        auto nearest_to_tower = std::make_unique<TowerDefense::NearestToTower>(*enemy_repository);

        auto tower_repository = std::make_unique<TowerDefense::TowerRepository>();
        std::unique_ptr<TowerDefense::SimpleTower> simple_tower1 = std::make_unique<TowerDefense::SimpleTower>(1, 12.3, 1, TowerDefense::Point(2, 4), nearest_to_tower.get(), 10.0, 0.2);
        std::unique_ptr<TowerDefense::SimpleTower> simple_tower2 = std::make_unique<TowerDefense::SimpleTower>(2, 12.3, 1, TowerDefense::Point(3, 5), nearest_to_tower.get(), 10.0, 0.2);
        tower_repository->add_tower(std::move(simple_tower1));
        tower_repository->add_tower(std::move(simple_tower2));
        REQUIRE(tower_repository->get_all().size() == 2);
        REQUIRE(tower_repository->get(2)->get_id() == 2);
        tower_repository->reset();
        REQUIRE(tower_repository->get_all().empty());
    }
    SECTION("Mapper Repository") {
        auto strategy_repository = std::make_unique<TowerDefense::StrategyRepository>();
        auto mapper_repository = std::make_unique<TowerDefense::MapperRepository>();
        auto castle_dto_mapper = std::make_unique<TowerDefense::CastleDTOMapper>();
        auto castle_mapper = std::make_unique<TowerDefense::CastleMapper>();
        auto enemy_dto_mapper = std::make_unique<TowerDefense::EnemyDTOMapper>();
        auto enemy_mapper = std::make_unique<TowerDefense::EnemyMapper>();
        auto tower_dto_mapper = std::make_unique<TowerDefense::SimpleTowerDTOMapper>(*strategy_repository);
        auto tower_mapper = std::make_unique<TowerDefense::SimpleTowerMapper>(*strategy_repository);
        mapper_repository->add_castle_dto_mapper(std::move(castle_dto_mapper));
        mapper_repository->add_castle_mapper(std::move(castle_mapper));
        mapper_repository->add_enemy_dto_mapper(std::move(enemy_dto_mapper));
        mapper_repository->add_enemy_mapper(std::move(enemy_mapper));
        mapper_repository->add_tower_dto_mapper(typeid(TowerDefense::SimpleTower), std::move(tower_dto_mapper));
        mapper_repository->add_tower_mapper("simple_tower",std::move(tower_mapper));
        TowerDefense::EnemyDTO enemy_dto {1, "enemy", 100, 150, 100, 120, 1, 4, 32, 160};
        auto enemy = mapper_repository->dto_to_enemy(enemy_dto);
        auto enemy_dto_2 = mapper_repository->enemy_to_dto(enemy.get());
        REQUIRE(enemy_dto_2 == enemy_dto);

        TowerDefense::CastleDTO castle_dto {1, "castle", 100, 150, 100, 120, 1};
        auto castle = mapper_repository->dto_to_castle(castle_dto);
        auto castle_dto_2 = mapper_repository->castle_to_dto(castle.get());
        REQUIRE(castle_dto_2 == castle_dto);
    }
}

TEST_CASE("Mapper") {
    SECTION("Castle mapper") {
        TowerDefense::CastleDTO dto {12, "castle", 100, 150, 1000, 24, 25};
        auto castle_mapper = std::make_unique<TowerDefense::CastleMapper>();
        auto castle_dto_mapper = std::make_unique<TowerDefense::CastleDTOMapper>();
        auto castle = castle_mapper->transform(dto);
        auto dto2 = castle_dto_mapper->transform(castle.get());
        REQUIRE(dto == dto2);
    }
    SECTION("Enemy mapper") {
        TowerDefense::EnemyDTO dto {115, "enemy", 100, 150, 100, 120, 1, 4, 32, 160};
        auto enemy_mapper = std::make_unique<TowerDefense::EnemyMapper>();
        auto enemy_dto_mapper = std::make_unique<TowerDefense::EnemyDTOMapper>();
        auto enemy = enemy_mapper->transform(dto);
        auto dto2 = enemy_dto_mapper->transform(enemy.get());
        REQUIRE(dto == dto2);
    }
    auto enemy_repository = std::make_unique<TowerDefense::EnemyRepository>();
    auto strategy_repository = std::make_unique<TowerDefense::StrategyRepository>();
    auto all_in_range = std::make_unique<TowerDefense::AllInRange>(*enemy_repository);
    auto weakest = std::make_unique<TowerDefense::Weakest>(*enemy_repository);
    strategy_repository->add_strategy("weakest", std::move(weakest));
    strategy_repository->add_strategy("all_in_range", std::move(all_in_range));

    TowerDefense::EffectConfig conf{{{"slow", 10, 10}, {"poison", 20, 10}, {"weakness", 10, 20}}};
    auto effect_factory = std::make_unique<TowerDefense::EffectFactory>(conf);
    SECTION("Simple tower mapper") {
        TowerDefense::TowerDTO dto {1, "simple_tower", 12.3, 1, 12, 14, 1000, "weakest", {{"damage", "10.0"}, {"rate_of_fire", "0.2"}}};
        auto tower_mapper = std::make_unique<TowerDefense::SimpleTowerMapper>(*strategy_repository);
        auto tower_dto_mapper = std::make_unique<TowerDefense::SimpleTowerDTOMapper>(*strategy_repository);
        auto tower = tower_mapper->transform(dto);
        auto dto2 = tower_dto_mapper->transform(tower.get());
        REQUIRE(dto.id == dto2.id);
        REQUIRE(dto.type == dto2.type);
        REQUIRE(dto.level == dto2.level);
        REQUIRE(dto.range == dto2.range);
        REQUIRE(std::stod(dto.properties.at("damage")) == std::stod(dto2.properties.at("damage")));
        REQUIRE(std::stod(dto.properties.at("rate_of_fire")) == std::stod(dto2.properties.at("rate_of_fire")));
    }
    SECTION("Magic tower mapper") {
        TowerDefense::TowerDTO dto {1, "magic_tower", 12.3, 1, 12, 14, 1000, "weakest", {{"damage", "10.0"}, {"rate_of_fire", "0.2"}, {"effect", "slow"}}};
        auto tower_mapper = std::make_unique<TowerDefense::MagicTowerMapper>(*strategy_repository, *effect_factory);
        auto tower_dto_mapper = std::make_unique<TowerDefense::MagicTowerDTOMapper>(*strategy_repository, *effect_factory);
        auto tower = tower_mapper->transform(dto);
        auto dto2 = tower_dto_mapper->transform(tower.get());
        REQUIRE(dto.id == dto2.id);
        REQUIRE(dto.type == dto2.type);
        REQUIRE(dto.level == dto2.level);
        REQUIRE(dto.range == dto2.range);
        REQUIRE(std::stod(dto.properties.at("damage")) == std::stod(dto2.properties.at("damage")));
        REQUIRE(std::stod(dto.properties.at("rate_of_fire")) == std::stod(dto2.properties.at("rate_of_fire")));
        REQUIRE(dto.properties.at("effect") == dto2.properties.at("effect"));
    }

    SECTION("Magic trap mapper") {
        TowerDefense::TowerDTO dto {1, "magic_trap", 12.3, 1, 12, 14, 1000, "all_in_range", { {"rate_of_fire", "0.2"}, {"effect", "slow"}}};
        auto tower_mapper = std::make_unique<TowerDefense::MagicTrapMapper>(*strategy_repository, *effect_factory);
        auto tower_dto_mapper = std::make_unique<TowerDefense::MagicTrapDTOMapper>(*strategy_repository, *effect_factory);
        auto tower = tower_mapper->transform(dto);
        auto dto2 = tower_dto_mapper->transform(tower.get());
        REQUIRE(dto.id == dto2.id);
        REQUIRE(dto.type == dto2.type);
        REQUIRE(dto.level == dto2.level);
        REQUIRE(dto.range == dto2.range);
        REQUIRE(std::stod(dto.properties.at("rate_of_fire")) == std::stod(dto2.properties.at("rate_of_fire")));
        REQUIRE(dto.properties.at("effect") == dto2.properties.at("effect"));
    }
}