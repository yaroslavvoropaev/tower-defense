add_library(imove_service INTERFACE IMoveService.h)

target_include_directories(imove_service INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)



