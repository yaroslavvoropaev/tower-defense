add_library(mapper_repository src/MapperRepository.cpp)

target_include_directories(mapper_repository PUBLIC include)
target_link_libraries(mapper_repository imapper_repository enemy_mapper
        castle_mapper simple_tower_mapper magic_tower_mapper magic_trap_mapper
        istrategy_repository ieffect_factory)