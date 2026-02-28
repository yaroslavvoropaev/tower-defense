add_library(iid_service INTERFACE IID_service.h)

target_include_directories(iid_service INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(iid_service INTERFACE id)



