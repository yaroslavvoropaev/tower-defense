add_library(strongest src/Strongest.cpp)

target_include_directories(strongest PUBLIC include)
target_link_libraries(strongest istrategy ienemy_repository)