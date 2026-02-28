add_library(istrategy_repository INTERFACE IStrategyRepository.h)

target_include_directories(istrategy_repository INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(istrategy_repository INTERFACE istrategy)