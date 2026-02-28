find_package(yaml-cpp REQUIRED)

add_library(yaml_state_service src/YamlStateService.cpp)

target_include_directories(yaml_state_service PUBLIC include)
target_link_libraries(yaml_state_service
        yaml-cpp istate_service imapper_repository ienemy_repository icastle_repository itower_repository)