add_library(weakest src/Weakest.cpp)

target_include_directories(weakest PUBLIC include)
target_link_libraries(weakest istrategy ienemy_repository)