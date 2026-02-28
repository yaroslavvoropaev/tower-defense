add_library(istrategy INTERFACE IStrategy.h)

target_include_directories(istrategy INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(istrategy INTERFACE ienemy)



