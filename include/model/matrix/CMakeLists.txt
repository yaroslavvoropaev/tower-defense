add_library(matrix INTERFACE Matrix.h)


target_include_directories(matrix INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)
