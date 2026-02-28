add_library(ienemy_mapper INTERFACE IEnemyMapper.h IEnemyDTOMapper.h)

target_include_directories(ienemy_mapper INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(ienemy_mapper INTERFACE dto ienemy)