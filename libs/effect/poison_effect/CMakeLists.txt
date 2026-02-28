add_library(poison_effect src/PoisonEffect.cpp)

target_include_directories(poison_effect PUBLIC include)
target_link_libraries(poison_effect ieffect ienemy)

