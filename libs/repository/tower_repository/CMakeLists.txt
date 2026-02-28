add_library(tower_repository src/TowerRepository.cpp)

target_include_directories(tower_repository PUBLIC include)
target_link_libraries(tower_repository itower_repository)


