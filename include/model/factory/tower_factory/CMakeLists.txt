add_library(itower_factory INTERFACE ITowerFactory.h)

target_include_directories(itower_factory INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(itower_factory INTERFACE abstract_tower)