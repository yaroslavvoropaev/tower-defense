add_library(effect_tower src/EffectTower.cpp)

target_include_directories(effect_tower PUBLIC include)

target_link_libraries(effect_tower ieffect)


