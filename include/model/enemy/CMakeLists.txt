add_library(ienemy INTERFACE IEffectable.h IEnemy.h IHealthable.h IMoveable.h)


target_include_directories(ienemy INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)


target_link_libraries(ienemy INTERFACE id point)


