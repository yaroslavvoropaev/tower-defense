add_library(slow_effect src/SlowEffect.cpp)

target_include_directories(slow_effect PUBLIC include)
target_link_libraries(slow_effect ieffect ienemy)

