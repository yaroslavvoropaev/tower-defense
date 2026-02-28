add_library(icastle_repository INTERFACE ICastleRepository.h)

target_include_directories(icastle_repository INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(icastle_repository INTERFACE icastle)