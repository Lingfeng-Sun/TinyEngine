cmake_minimum_required(VERSION 3.19)


### Require out-of-source builds
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory (or any directory with "
                        "CMakeLists.txt file). Please make a build subdirectory. Feel free to "
                        "remove CMakeCache.txt and CMakeFiles.")
endif()


project(
    TinyEngine
    VERSION 1.0
    LANGUAGES CXX
)

if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(CMAKE_CXX_EXTENSIONS OFF)
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif()


function(set_target_warnning targetName)
	target_compile_options(${targetName} PUBLIC
		$<$<CXX_COMPILER_ID:MSVC>:/W4 /WX /wd4100 /wd4251 /wd4101>
		$<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror -Wno-unused-private-field -Wno-unused-parameter -Wno-unused-variable -nostdinc++ -Wno-deprecated>)
endfunction()


function(enable_unity_build TARGET) 
	get_target_property(SRCS ${TARGET} SOURCES) 
	set(UNITY_SOURCE_FILE ${CMAKE_CURRENT_BINARY_DIR}/${TARGET}_unity_build.cpp) 
	file(WRITE ${UNITY_SOURCE_FILE} "// Unity Build file for ${TARGET}\n") 
	
	foreach(SRC ${SRCS}) 
		file(APPEND ${UNITY_SOURCE_FILE} "#include \"${SRC}\"\n") 
	endforeach() 

	set_source_files_properties(${UNITY_SOURCE_FILE} PROPERTIES GENERATED TRUE) 
	target_sources(${TARGET} PRIVATE ${UNITY_SOURCE_FILE}) 
endfunction()



set(CMAKE_LIBRARY_ARCHITECTURE x86_64)

option(TINY_SHIPPING "Enable for final public release build" OFF)


set(compiler_folder_name "")
if(WIN32)
	if(MSVC_TOOLSET_VERSION STREQUAL "143")
		set(compiler_folder_name "vs2022")
	else()
		message(FATAL_ERROR "we only support vs2022 config for now.")
	endif()

	set (LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/Bin/Win/x64/${compiler_folder_name})
	set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Bin/Win/x64/${compiler_folder_name})
elseif(LINUX)
	set (LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/../Bin/Linux/x64/)
	set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Bin/Linux/x64)
	
	#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -v")
	#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++ -I/user/include/c++/8/  -lc++abi")
	#CMAKE_CROSSCOMPILING
else()
	set (LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/Bin/Mac/x64/)
	set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Bin/Mac/x64)
endif()


if(MSVC)
    add_definitions(-DUNICODE -D_UNICODE -D_WIN32_WINNT=0x0602)
endif()


if(TINY_SHIPPING)
	set_property(DIRECTORY APPEND PROPERTY COMPILE_DEFINITIONS $<$<CONFIG:RELEASE>:TINY_SHIPPING>)
	add_definitions(-DHOYOAI_SHIPPING)
endif()


add_subdirectory(Infrastructure)
add_subdirectory(Global)
add_subdirectory(BaseLib)



if(WIN32)
	add_subdirectory(TestConsole)
endif()