find_package(yaml-cpp REQUIRED)
add_library(loader src/Loader.cpp)

target_include_directories(loader PUBLIC include)
target_link_libraries(loader iloader dto yaml-cpp

        strategy_repository mapper_repository tower_repository enemy_repository castle_repository

        id_service enemy_service tower_service economy_service move_service yaml_state_service

        weakest strongest all_in_range nearest_to_tower nearest_to_castle

        effect_factory tower_factory enemy_factory castle_factory

        simple_tower_mapper magic_tower_mapper magic_trap_mapper enemy_mapper castle_mapper

        simple_tower_attack_visitor magic_tower_attack_visitor magic_trap_attack_visitor
        simple_tower_upgrade_visitor magic_tower_upgrade_visitor magic_trap_upgrade_visitor

        game_field

        presenter)

