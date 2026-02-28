add_library(tower_factory src/TowerFactory.cpp)

target_include_directories(tower_factory PUBLIC include)
target_link_libraries(tower_factory itower_factory dto simple_tower magic_tower magic_trap
                                        istrategy_repository ieffect_factory icastle_repository iid_service)