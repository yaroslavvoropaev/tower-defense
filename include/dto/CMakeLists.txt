add_library(dto INTERFACE dto.h)

target_include_directories(dto INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(dto INTERFACE id)