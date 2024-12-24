message(STATUS "Configuring BaseLib...")


Set(BaesLib_H
./include/TinyLog.h
)

Set(BaesLib_S
./src/BaseLib.cpp
./src/TinyLog.cpp
)

add_library(BaesLib STATIC 
    ${BaesLib_H}
    ${BaesLib_S}
)

target_compile_features(BaesLib PUBLIC cxx_std_14)
set_target_warnning(BaesLib)

if(TINY_USE_SHARED_LIB)
	target_compile_definitions(BaesLib PRIVATE "BaesLib_EXPORTS")
endif()


target_include_directories(Global PUBLIC 
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

list(APPEND BaesLib_LinkLib
	Global
)

target_link_libraries(BaesLib ${BaesLib_LinkLib})