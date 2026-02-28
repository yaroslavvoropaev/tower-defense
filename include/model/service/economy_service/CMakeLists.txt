add_library(ieconomy_service INTERFACE IEconomyService.h)

target_include_directories(ieconomy_service INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(ieconomy_service INTERFACE id iupgrade_visitor)


