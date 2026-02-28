add_library(id_service src/ID_service.cpp)

target_include_directories(id_service PUBLIC include)
target_link_libraries(id_service iid_service)