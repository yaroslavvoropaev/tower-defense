add_library(istate_service INTERFACE IStateService.h)

target_include_directories(istate_service INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)



