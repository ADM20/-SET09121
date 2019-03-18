cmake_minimum_required(VERSION 3.11)
# Require modern C++
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Games_Engineering)

#### Setup Directories ####
#Main output directory

SET(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
# Ouput all DLLs from all libs into main build folder
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

#Resources
add_custom_target(copy_resources ALL COMMAND ${CMAKE_COMMAND} 
  -E copy_directory
    "${PROJECT_SOURCE_DIR}/res"
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIGURATION>/res
)

#### Add External Dependencies ####
add_subdirectory("lib/sfml")
set(SFML_INCS "lib/sfml/include")
link_directories("${CMAKE_BINARY_DIR}/lib/sfml/lib")

### BOX 2D PHYSICS LIBRARY ###
add_subdirectory("lib/b2d/Box2D")
set(B2D_INCS "lib/b2d/Box2D/")
#link_directories("${CMAKE_BINARY_DIR}/lib/sfml/lib")

#### practical_1 ####
file(GLOB_RECURSE SOURCES practical_1/*.cpp practical_1/*.h)
add_executable(PRACTICAL_1 ${SOURCES})
target_include_directories(PRACTICAL_1 PRIVATE ${SFML_INCS})
set(EXECUTABLES ${EXECUTABLES} PRACTICAL_1)

#### practical_2 ####
file(GLOB_RECURSE SOURCES practical_2/*.cpp practical_2/*.h)
add_executable(PRACTICAL_2 ${SOURCES})
target_include_directories(PRACTICAL_2 SYSTEM PRIVATE ${SFML_INCS})
set(EXECUTABLES ${EXECUTABLES} PRACTICAL_2)

#### practical_3 ####
file(GLOB_RECURSE SOURCES practical_3/*.cpp practical_3/*.h)
add_executable(PRACTICAL_3 ${SOURCES})
target_include_directories(PRACTICAL_3 SYSTEM PRIVATE ${SFML_INCS})
set(EXECUTABLES ${EXECUTABLES} PRACTICAL_3)

#### practical_4####
file(GLOB_RECURSE SOURCES practical_4/*.cpp practical_4/*.h)
add_executable(PRACTICAL_4 ${SOURCES})
target_include_directories(PRACTICAL_4 SYSTEM PRIVATE ${SFML_INCS})
set(EXECUTABLES ${EXECUTABLES} PRACTICAL_4)

### practical_5###
file(GLOB_RECURSE SOURCES practical_5/*.cpp practical_5/*.h)
add_executable(PRACTICAL_5 ${SOURCES})
target_include_directories(PRACTICAL_5 SYSTEM PRIVATE ${SFML_INCS} ${B2D_INCS})
set(EXECUTABLES ${EXECUTABLES} PRACTICAL_5)

### practical_6###
file(GLOB_RECURSE SOURCES practical_6/*.cpp practical_6/*.h)
file(GLOB_RECURSE CMPNTS practical_6/components/*.cpp practical_6/components/*.h)
file(GLOB_RECURSE SCENES practical_6/scenes/*.cpp practical_6/scenes/*.h)
add_executable(PRACTICAL_6 ${SOURCES} ${RESOURCE_FILES})
source_group("components" FILES ${CMPNTS})
source_group("resources" FILES ${RESOURCE_FILES})
target_include_directories(PRACTICAL_6 SYSTEM PRIVATE ${SFML_INCS} ${B2D_INCS})
set(EXECUTABLES ${EXECUTABLES} PRACTICAL_6)

### practical_7 ###
file(GLOB_RECURSE SOURCES practical_7/*.cpp practical_7/*.h)
file(GLOB_RECURSE CMPNTS practical_7/components/*.cpp practical_7/components/*.h)
file(GLOB_RECURSE SCENES practical_7/scenes/*.cpp practical_7/scenes/*.h)
add_executable(PRACTICAL_7 ${SOURCES} ${CMPNTS} ${SCENES} ${RESOURCE_FILES})
source_group("components" FILES ${CMPNTS})
source_group("resources" FILES ${RESOURCE_FILES})
target_include_directories(PRACTICAL_7 SYSTEM PRIVATE ${SFML_INCS} ${B2D_INCS})
target_link_libraries(PRACTICAL_7 lib_engine)
set(EXECUTABLES ${EXECUTABLES} PRACTICAL_7)

## 8 - Decisions
file(GLOB_RECURSE SOURCES practical_8/*.cpp practical_8/*.h)
file(GLOB_RECURSE CMPNTS practical_8/components/*.cpp practical_8/components/*.h)
file(GLOB_RECURSE SCENES practical_8/scenes/*.cpp practical_8/scenes/*.h)
add_executable(PRACTICAL_8 ${SOURCES} ${CMPNTS} ${SCENES} ${RESOURCE_FILES})
target_link_libraries(PRACTICAL_8 lib_engine)
set(EXECUTABLES ${EXECUTABLES} PRACTICAL_8)

## 9 - Deployment ###
file(GLOB_RECURSE SOURCES practical_9/*.cpp practical_9/*.h)
add_executable(PRACTICAL_9 ${SOURCES} ${RESOURCE_FILES})
set(EXECUTABLES ${EXECUTABLES} PRACTICAL_9)

#### LINK DEPENDENCIES ####
foreach(exe ${EXECUTABLES})
	#Set working directory to build dir in visual studio
	set_target_properties(${exe} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration))
	#Add all SFML libs 
	target_link_libraries(${exe}
		optimized sfml-graphics debug sfml-graphics-d
		optimized sfml-audio debug sfml-audio-d
		optimized sfml-window debug sfml-window-d
		optimized sfml-system debug sfml-system-d
		optimized sfml-graphics debug sfml-graphics-d
		optimized sfml-main debug sfml-main-d
		lib_tile_level_loader
		lib_ecm
		Box2D
		lib_engine)
 if(MSVC) # Hide Console in release builds
    set_target_properties(${exe} PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS")
  endif(MSVC)
  
	add_dependencies(${exe} sfml-graphics sfml-audio copy_resources)
endforeach ()

 


### TILE LOADER LIBRARY ###
file(GLOB_RECURSE SOURCE_FILES lib_tile_level_loader/*.cpp lib_tile_level_loader/*.h)
add_library(lib_tile_level_loader STATIC ${SOURCE_FILES})
target_include_directories(lib_tile_level_loader INTERFACE "${CMAKE_SOURCE_DIR}/lib_tile_level_loader/")
target_link_libraries(lib_tile_level_loader lib_maths sfml-graphics)

### MATHS LIBRARY ###
add_library(lib_maths INTERFACE)
target_sources(lib_maths INTERFACE "${CMAKE_SOURCE_DIR}/lib_maths/maths.h")
target_include_directories(lib_maths INTERFACE "${CMAKE_SOURCE_DIR}/lib_maths" SYSTEM INTERFACE "${SFML_INCS}")

### ENGINE LIBRARY ###
file(GLOB_RECURSE SOURCE_FILES engine/*.cpp engine/*.h)
add_library(lib_engine STATIC ${SOURCE_FILES} ${RESOURCE_FILES})
target_include_directories(lib_engine INTERFACE "${CMAKE_SOURCE_DIR}/engine/" PUBLIC SYSTEM ${B2D_INCS} )
target_link_libraries(lib_engine lib_tile_level_loader lib_maths lib_ecm Box2D sfml-graphics sfml-audio)

### ECM LIBRARY ###
file(GLOB_RECURSE SOURCE_FILES lib_ecm/*.cpp lib_ecm/*.h)
add_library(lib_ecm STATIC ${SOURCE_FILES})
target_include_directories(lib_ecm INTERFACE "${CMAKE_SOURCE_DIR}/lib_ecm")
target_link_libraries(lib_ecm PRIVATE lib_maths)

#Install directory within build folder, so it doesn't go into /lib or program-files
set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install/")
#Installer.exe/zip built into /installer
SET(CPACK_PACKAGE_DIRECTORY "${CMAKE_BINARY_DIR}/installer/")

#Install component for runtime dlls and stuff
set(CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_SKIP TRUE) #stop this happening on non-release buildss
INCLUDE(InstallRequiredSystemLibraries)
install( PROGRAMS ${CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS} DESTINATION "bin/" CONFIGURATIONS Release COMPONENT System )
#Install component for resources
install(DIRECTORY "${PROJECT_SOURCE_DIR}/res" DESTINATION "bin/" CONFIGURATIONS Release COMPONENT resources_cmpt)
#We disabled SFML's INSTALL component as it brings along junk, so we gotta make one ourselves
install(DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/" DESTINATION "bin" CONFIGURATIONS Release COMPONENT libs_cmpt FILES_MATCHING PATTERN "*.dll" )

#Tell CPack about the libs and resources install components
set(CPACK_COMPONENTS_ALL ${CPACK_COMPONENTS_ALL} resources_cmpt libs_cmpt)
#CPACK_INSTALL_CMAKE_PROJECTS IS only necessary if not using CPACK_COMPONENTS_ALL
#set(CPACK_INSTALL_CMAKE_PROJECTS ${CPACK_INSTALL_CMAKE_PROJECTS};${CMAKE_BINARY_DIR};${CMAKE_PROJECT_NAME};resources_cmpt;/)
#set(CPACK_INSTALL_CMAKE_PROJECTS ${CPACK_INSTALL_CMAKE_PROJECTS};${CMAKE_BINARY_DIR};${CMAKE_PROJECT_NAME};libs_cmpt;/)

#Install component for all labs, also tell CPack about them
foreach (exe ${EXECUTABLES})
  install(TARGETS ${exe} DESTINATION "bin" CONFIGURATIONS Release COMPONENT ${exe}_cmpt )
  #set(CPACK_INSTALL_CMAKE_PROJECTS ${CPACK_INSTALL_CMAKE_PROJECTS};${CMAKE_BINARY_DIR};${CMAKE_PROJECT_NAME};${exe}_cmpt;/)
  set(CPACK_COMPONENTS_ALL ${CPACK_COMPONENTS_ALL} ${exe}_cmpt)
  set(CPACK_COMPONENT_${exe}_CMPT_DEPENDS resources_cmpt libs_cmpt)
  set(CPACK_COMPONENT_${exe}_CMPT_GROUP "Labs")
endforeach ()


IF(WIN32)
  set(CPACK_GENERATOR NSIS)
  set(CPACK_NSIS_COMPONENT_INSTALL ON)
  set(CPACK_NSIS_HELP_LINK "https://github.com/edinburgh-napier/set09121")
  set(CPACK_NSIS_URL_INFO_ABOUT "https://github.com/edinburgh-napier/set09121")
  set(CPACK_NSIS_CONTACT "https://github.com/edinburgh-napier")
ELSE()
  set(CPACK_GENERATOR ZIP)
ENDIF(WIN32)


set(CPACK_PACKAGE_FILE_NAME ${CMAKE_PROJECT_NAME})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "set09119")
set(CPACK_PACKAGE_VENDOR "Edinburgh Napier University")
find_file (LICENSE NAMES LICENSE LICENSE.txt PATHS  "${CMAKE_SOURCE_DIR}/../" "${CMAKE_SOURCE_DIR}" NO_DEFAULT_PATH)
if(${LICENSE})
  set(CPACK_RESOURCE_FILE_LICENSE ${LICENSE})
endif(${LICENSE})
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "1")
set(CPACK_PACKAGE_VERSION_PATCH "0")

INCLUDE(CPack)
