add_library(magic_trap src/MagicTrap.cpp)

target_include_directories(magic_trap PUBLIC include)
target_link_libraries(magic_trap abstract_tower effect_tower)