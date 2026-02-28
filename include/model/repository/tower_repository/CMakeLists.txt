add_library(itower_repository INTERFACE ITowerRepository.h)

target_include_directories(itower_repository INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(itower_repository INTERFACE abstract_tower)