cmake_minimum_required(VERSION 3.10)
project(twitch-addon)

set(SOURCES src/twitch_addon.cpp)

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
target_include_directories(${PROJECT_NAME} PRIVATE ${NODE_ADDON_API_DIR})
add_definitions(-DNAPI_VERSION=3)
