# 3.13 is needed for the VS_DEBUGGER_COMMAND stuff
cmake_minimum_required(VERSION 3.13)
project(twitch-addon)

set(SOURCES src/obs.hpp
    src/obs.cpp
    src/twitch_addon.cpp
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

# helper stuff for Visual studio
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT twitch-addon)
# with the approach below pdbs are not loaded since the debugger actually can't see what libraries are loaded due to the fact that the cmd process is detached
#set_target_properties(twitch-addon PROPERTIES VS_DEBUGGER_COMMAND "C:\\Windows\\System32\\cmd" VS_DEBUGGER_COMMAND_ARGUMENTS "/c \"npm start\"" VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/../electron-quick-start")
# this seems better but now node modules seem to be failing
set_target_properties(twitch-addon PROPERTIES VS_DEBUGGER_COMMAND "node.exe" VS_DEBUGGER_COMMAND_ARGUMENTS "main.js" VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/../electron-quick-start")