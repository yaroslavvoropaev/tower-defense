add_library(ipresenter INTERFACE IPresenter.h)

target_include_directories(ipresenter INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(ipresenter INTERFACE dto)