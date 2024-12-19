message(STATUS "Configuring Infrastructure...")


Set(Infra_H
./include/GlobalSingleton.h
)

Set(Infra_S
./src/GlobalSingleton.cpp
)



add_library(TinyInfra SHARED 
${Infra_H}
${Infra_S}
)

target_compile_features(TinyInfra PUBLIC cxx_std_14)
set_target_warnning(TinyInfra)

#target_compile_definitions(TinyInfra PUBLIC HOYOAI_BUILD_DYNAMIC_LIB)
target_compile_definitions(TinyInfra PRIVATE "TinyInfra_EXPORTS")

list(APPEND Infra_LinkLib
)

target_link_libraries(TinyInfra ${Infra_LinkLib})