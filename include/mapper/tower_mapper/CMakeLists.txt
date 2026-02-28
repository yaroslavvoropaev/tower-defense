add_library(itower_mapper INTERFACE ITowerDTOMapper.h ITowerMapper.h)

target_include_directories(itower_mapper INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(itower_mapper INTERFACE dto abstract_tower)