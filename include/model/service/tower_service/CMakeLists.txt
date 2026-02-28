add_library(itower_service INTERFACE ITowerService.h)

target_include_directories(itower_service INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(itower_service INTERFACE iattack_visitor)
