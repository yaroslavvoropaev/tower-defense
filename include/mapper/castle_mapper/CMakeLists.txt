add_library(icastle_mapper INTERFACE ICastleMapper.h ICastleDtoMapper.h)

target_include_directories(icastle_mapper INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(icastle_mapper INTERFACE dto icastle)