add_library(point INTERFACE Point.h)

target_include_directories(point INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)
