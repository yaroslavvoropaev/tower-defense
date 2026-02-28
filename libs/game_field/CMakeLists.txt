add_library(game_field src/GameFiled.cpp)

target_include_directories(game_field PUBLIC include)
target_link_libraries(game_field matrix id)