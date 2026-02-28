#add_compile_options(-fsanitize=thread)
#add_link_options(-fsanitize=thread)
add_compile_options(-pthread)


add_executable(timing_main timing.cpp)

target_link_libraries(timing_main loader simple_tower nearest_to_tower enemy)
