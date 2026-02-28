add_library(imapper_repository INTERFACE IMapperRepository.h)

target_include_directories(imapper_repository INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(imapper_repository INTERFACE ienemy abstract_tower icastle dto
                                            ienemy_mapper itower_mapper icastle_mapper)