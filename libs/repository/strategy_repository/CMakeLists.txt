add_library(strategy_repository src/StrategyRepository.cpp)

target_include_directories(strategy_repository PUBLIC include)
target_link_libraries(strategy_repository istrategy_repository ienemy_repository icastle_repository
                                            weakest strongest nearest_to_castle nearest_to_tower all_in_range)