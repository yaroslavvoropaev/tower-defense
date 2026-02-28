add_library(iupgrade_visitor INTERFACE IUpgradeVisitor.h)

target_include_directories(iupgrade_visitor INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(iupgrade_visitor INTERFACE dto)




