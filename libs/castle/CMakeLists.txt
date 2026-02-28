add_library(castle src/Castle.cpp)

target_include_directories(castle PUBLIC include)
target_link_libraries(castle icastle)