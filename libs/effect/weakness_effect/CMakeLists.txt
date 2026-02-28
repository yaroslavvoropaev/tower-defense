add_library(weakness_effect src/WeaknessEffect.cpp)

target_include_directories(weakness_effect PUBLIC include)
target_link_libraries(weakness_effect ieffect ienemy)



