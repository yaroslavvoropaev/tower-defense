add_library(iloader INTERFACE ILoader.h)

target_include_directories(iloader INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(iloader INTERFACE icastle_repository ienemy_repository itower_repository ienemy_repository imapper_repository

                                        ieffect_factory ienemy_factory itower_factory

                                        iid_service economy_service enemy_service tower_service imove_service istate_service

                                        game_field dto

                                        ipresenter icastle_factory
)