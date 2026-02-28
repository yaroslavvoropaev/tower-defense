add_library(presenter src/Presenter.cpp)

target_include_directories(presenter PUBLIC include)
target_link_libraries(presenter ipresenter ienemy_repository itower_repository icastle_repository imapper_repository
                itower_factory ienemy_factory imove_service game_field itower_service ienemy_service ieconomy_service istate_service iid_service icastle_factory)