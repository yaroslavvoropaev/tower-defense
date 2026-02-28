add_library(ienemy_repository INTERFACE IEnemyRepository.h)

target_include_directories(ienemy_repository INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(ienemy_repository INTERFACE ienemy)