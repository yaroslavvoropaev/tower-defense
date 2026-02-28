add_library(enemy src/Enemy.cpp)

target_include_directories(enemy PUBLIC include)
target_link_libraries(enemy ienemy module)