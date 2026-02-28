add_library(abstract_tower src/AbstractTower.cpp)

target_include_directories(abstract_tower PUBLIC include)

target_link_libraries(abstract_tower id point ienemy iattack_visitor iupgrade_visitor istrategy dto)


