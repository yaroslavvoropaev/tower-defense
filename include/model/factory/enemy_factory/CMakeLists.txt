add_library(ienemy_factory INTERFACE IEnemyFactory.h)

target_include_directories(ienemy_factory INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(ienemy_factory INTERFACE ienemy)