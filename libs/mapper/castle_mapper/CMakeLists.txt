add_library(castle_mapper src/CastleMapper.cpp src/CastleDTOMapper.cpp)

target_include_directories(castle_mapper PUBLIC include)
target_link_libraries(castle_mapper icastle_mapper castle)