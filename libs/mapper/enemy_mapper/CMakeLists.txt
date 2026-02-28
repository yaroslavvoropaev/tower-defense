add_library(enemy_mapper src/EnemyMapper.cpp src/EnemyDTOMapper.cpp)

target_include_directories(enemy_mapper PUBLIC include)
target_link_libraries(enemy_mapper ienemy_mapper enemy)