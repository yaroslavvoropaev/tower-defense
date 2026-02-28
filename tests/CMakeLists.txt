find_package(Catch2 3 REQUIRED)

add_compile_options(--coverage)
add_link_options(--coverage)

add_executable(testing_main testing.cpp)

target_link_libraries(testing_main Catch2::Catch2WithMain)
target_link_libraries(testing_main matrix game_field enemy castle
                                            castle_mapper enemy_mapper simple_tower_mapper magic_tower_mapper magic_trap_mapper
                                            castle_factory effect_factory enemy_factory tower_factory
                                            simple_tower magic_tower magic_trap
                                            simple_tower_attack_visitor magic_tower_attack_visitor magic_trap_attack_visitor
                                            simple_tower_upgrade_visitor magic_tower_upgrade_visitor magic_trap_upgrade_visitor
                                            weakest nearest_to_castle nearest_to_tower strongest all_in_range
                                            enemy_repository castle_repository tower_repository strategy_repository mapper_repository
                                            economy_service enemy_service move_service tower_service id_service yaml_state_service
                                            poison_effect weakness_effect slow_effect)