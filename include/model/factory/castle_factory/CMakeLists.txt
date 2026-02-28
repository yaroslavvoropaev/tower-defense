add_library(icastle_factory INTERFACE ICastleFactory.h)

target_include_directories(icastle_factory INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(icastle_factory INTERFACE icastle)