add_library(View src/View.cpp)

target_include_directories(View PUBLIC include)

target_link_libraries(View dto presenter)