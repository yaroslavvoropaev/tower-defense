add_library(ienemy_service INTERFACE IEnemyService.h)

target_include_directories(ienemy_service INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)



