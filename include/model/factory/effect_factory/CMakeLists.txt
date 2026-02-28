add_library(ieffect_factory INTERFACE IEffectFactory.h)


target_include_directories(ieffect_factory INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)



target_link_libraries(ieffect_factory INTERFACE ieffect)