add_library(iattack_visitor INTERFACE IAttackVisitor.h)


target_include_directories(iattack_visitor INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)


target_link_libraries(iattack_visitor INTERFACE dto)


