# 3.13 is needed for the VS_DEBUGGER_COMMAND stuff
cmake_minimum_required(VERSION 3.13)
project(twitch-addon)
set(CMAKE_CXX_STANDARD 17)

set(SOURCES src/obs.hpp
    src/obs.cpp
    src/twitch_addon.cpp
    src/unicode.hpp
    src/unicode.cpp
)

include(../obs-studio-install/cmake/LibObs/LibObsConfig.cmake)

add_library(twitch-addon SHARED ${SOURCES} ${CMAKE_JS_SRC})
set_target_properties(twitch-addon PROPERTIES PREFIX "" SUFFIX ".node")
message(INFO "node api includes: ${CMAKE_JS_INC}")
target_include_directories(twitch-addon PRIVATE ../obs-studio-install/include ${CMAKE_JS_INC})
target_link_libraries(twitch-addon ${CMAKE_JS_LIB} ${LIBOBS_LIBRARIES})

execute_process(COMMAND node -p "require('node-addon-api').include"
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE NODE_ADDON_API_DIR
    )
string(REPLACE "\n" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})
string(REPLACE "\"" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})
target_include_directories(twitch-addon PRIVATE ${NODE_ADDON_API_DIR})
add_definitions(-DNAPI_VERSION=3)
add_custom_command(TARGET twitch-addon POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:twitch-addon>" "${CMAKE_SOURCE_DIR}/../electron-quick-start/node_modules/twitch-addon/$<TARGET_FILE_NAME:twitch-addon>")
add_custom_target(copy-obs-runtime 
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/../obs-studio-install/bin/64bit" "${CMAKE_SOURCE_DIR}/../electron-quick-start/node_modules/twitch-addon"
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/../obs-studio-install/data" "${CMAKE_SOURCE_DIR}/../electron-quick-start/node_modules/twitch-addon/data"
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/../obs-studio-install/obs-plugins/64bit" "${CMAKE_SOURCE_DIR}/../electron-quick-start/node_modules/twitch-addon/obs-plugins"
)


# helper stuff for Visual studio
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT twitch-addon)
set_target_properties(twitch-addon PROPERTIES VS_DEBUGGER_COMMAND "${CMAKE_SOURCE_DIR}/../electron-quick-start/node_modules/electron/dist/electron.exe" VS_DEBUGGER_COMMAND_ARGUMENTS "${CMAKE_SOURCE_DIR}/../electron-quick-start/" VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/../electron-quick-start")
