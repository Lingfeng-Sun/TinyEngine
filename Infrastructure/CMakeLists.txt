message(STATUS "Configuring Infrastructure...")


Set(Infra_H
./include/TinyCommon.h
./include/ContainerDefine.h
./include/CommanMacroDef.h
./include/TinyAssert.h
./include/ReferenceCountObject.h
./include/TinyNewDelete.h
)

Set(Infra_S
./src/Infrastructure.cpp
)


add_library(TinyInfra STATIC 
${Infra_H}
${Infra_S}
)

target_compile_features(TinyInfra PUBLIC cxx_std_14)
set_target_warnning(TinyInfra)

#target_compile_definitions(TinyInfra PUBLIC HOYOAI_BUILD_DYNAMIC_LIB)
target_compile_definitions(TinyInfra PRIVATE "TinyInfra_EXPORTS")

target_include_directories(TinyInfra PUBLIC 
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)


list(APPEND Infra_LinkLib
)
target_link_libraries(TinyInfra ${Infra_LinkLib})