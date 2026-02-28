add_library(icastle INTERFACE ICastle.h IEconomyable.h)

target_include_directories(icastle INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(icastle INTERFACE id point)