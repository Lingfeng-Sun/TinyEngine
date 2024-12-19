message(STATUS "Configuring BaseLib...")


Set(BaesLib_H
./include/TinyAssert.h
./include/TinyLog.h
)

Set(BaesLib_S
./src/TinyLog.cpp
)



add_library(BaesLib STATIC 
    ${BaesLib_H}
    ${BaesLib_S}
)

target_compile_features(BaesLib PUBLIC cxx_std_14)
set_target_warnning(BaesLib)

target_compile_definitions(BaesLib PRIVATE "BaesLib_EXPORTS")

list(APPEND BaesLib_LinkLib
)

target_link_libraries(BaesLib ${BaesLib_LinkLib})