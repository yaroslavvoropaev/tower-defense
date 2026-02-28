cmake_minimum_required(VERSION 4.0)
project(tower_defense)

find_package(TBB REQUIRED)
link_libraries(TBB::tbb)


set(CMAKE_CXX_STANDARD 20)
add_compile_options(-g -Wall -Wextra)

add_compile_options(--coverage)
add_link_options(--coverage)

add_compile_options(-ltbb)


add_subdirectory(include)
add_subdirectory(loader)
add_subdirectory(libs)
add_subdirectory(tests)
add_subdirectory(timing)

add_executable(main main.cpp)
target_link_libraries(main loader)
target_link_libraries( main presenter)
target_link_libraries(main sfml-graphics sfml-window sfml-system)
target_link_libraries(main View)
target_link_libraries(main matrix)



