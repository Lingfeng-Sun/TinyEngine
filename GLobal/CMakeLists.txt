message(STATUS "Configuring Global...")


Set(Global_H
./include/Global.h
./include/GlobalExport.h
)

Set(Global_S
./src/Global.cpp
)

add_library(Global SHARED 
${Global_H}
${Global_S}
)

target_compile_features(Global PUBLIC cxx_std_14)
set_target_warnning(Global)

target_compile_definitions(Global PRIVATE "Global_EXPORTS")

target_include_directories(Global PUBLIC)

set(Global_Includes
	./../ThirdParty/mimalloc/include
)

target_include_directories(Global PUBLIC 
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	${Global_Includes}
)

set(Global_LinkLib
	TinyInfra
)

set(MIMALLOC_BASE_PATH ${CMAKE_SOURCE_DIR}/ThirdParty/mimalloc/lib/win/vs2022)

target_link_libraries(Global PUBLIC ${Global_LinkLib}
	$<$<CONFIG:Debug>:${MIMALLOC_BASE_PATH}/Debug/mimalloc.lib> 
	$<$<CONFIG:RelWithDebInfo>:${MIMALLOC_BASE_PATH}/RelWithDebInfo/mimalloc.lib>
	$<$<CONFIG:Release>:${MIMALLOC_BASE_PATH}/Release//mimalloc.lib>
)

add_custom_command(TARGET Global POST_BUILD 
	COMMAND ${CMAKE_COMMAND}  -E copy_if_different
	$<$<CONFIG:Debug>:${MIMALLOC_BASE_PATH}/$<CONFIG>/mimalloc.dll> 
	$<$<CONFIG:RelWithDebInfo>:${MIMALLOC_BASE_PATH}/$<CONFIG>/mimalloc.dll>
	$<$<CONFIG:Release>:${MIMALLOC_BASE_PATH}/$<CONFIG>/mimalloc.dll>
	${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/mimalloc.dll

	COMMAND ${CMAKE_COMMAND}  -E copy_if_different
	$<$<CONFIG:Debug>:${MIMALLOC_BASE_PATH}/$<CONFIG>/mimalloc-redirect.dll> 
	$<$<CONFIG:RelWithDebInfo>:${MIMALLOC_BASE_PATH}/$<CONFIG>/mimalloc-redirect.dll>
	$<$<CONFIG:Release>:${MIMALLOC_BASE_PATH}/$<CONFIG>/mimalloc-redirect.dll>
	${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/mimalloc-redirect.dll
)