message(STATUS "Configuring: Test TestConsole...")

set(CONSOLE_H
	stb_image.h
)

set(CONSOLE_S
	main.cpp
)

add_executable(TestConsole ${CONSOLE_H} ${CONSOLE_S})

target_compile_features(TestConsole PUBLIC cxx_std_14)

target_include_directories(TestConsole PRIVATE 
	${CMAKE_CURRENT_SOURCE_DIR}
)
set_target_warnning(TestConsole)

target_link_libraries(TestConsole PUBLIC 
	Global 
	BaesLib
)

