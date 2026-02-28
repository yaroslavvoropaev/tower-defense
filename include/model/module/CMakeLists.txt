add_library(module src/EffectModule.cpp src/HealthModule.cpp src/MoveModule.cpp)


target_include_directories(module PUBLIC include)

target_link_libraries(module ieffect point)

