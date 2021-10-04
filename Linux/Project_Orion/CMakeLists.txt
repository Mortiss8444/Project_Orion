CMAKE_MINIMUM_REQUIRED(VERSION 3.16.3)
PROJECT(ProjectOrion)

SET(CMAKE_CXX_STANDARD 14)
SET(CMAKE_BUILD_TYPE DEBUG)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

include_directories(${CMAKE_SOURCE_DIR}/Dependancies/glfw)
link_directories(${CMAKE_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE})

include_directories(${CMAKE_SOURCE_DIR}/Dependancies/glfw/src)
link_directories(${CMAKE_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE})

FIND_PACKAGE(OpenGL REQUIRED)
FIND_PACKAGE(Freetype REQUIRED)

ADD_EXECUTABLE(${PROJECT_NAME} 
${CMAKE_CURRENT_SOURCE_DIR}/Main.cpp 
${CMAKE_CURRENT_SOURCE_DIR}/GLmain.h 
${CMAKE_CURRENT_SOURCE_DIR}/handler.h 
${CMAKE_CURRENT_SOURCE_DIR}/handler.cpp 
${CMAKE_CURRENT_SOURCE_DIR}/Glob_vars.cpp 
${CMAKE_CURRENT_SOURCE_DIR}/GLmain.cpp 
${CMAKE_CURRENT_SOURCE_DIR}/TextRenderer.h 
${CMAKE_CURRENT_SOURCE_DIR}/TextRenderer.cpp 
${CMAKE_CURRENT_SOURCE_DIR}/Texture.h 
${CMAKE_CURRENT_SOURCE_DIR}/Texture.cpp 
${CMAKE_CURRENT_SOURCE_DIR}/MapRenderer.h 
${CMAKE_CURRENT_SOURCE_DIR}/MapRenderer.cpp 
${CMAKE_CURRENT_SOURCE_DIR}/Sat_class.h 
${CMAKE_CURRENT_SOURCE_DIR}/Sat_class.cpp 
${CMAKE_CURRENT_SOURCE_DIR}/math_lib.h 
${CMAKE_CURRENT_SOURCE_DIR}/math_lib.cpp 
${CMAKE_CURRENT_SOURCE_DIR}/shader.h 
${CMAKE_CURRENT_SOURCE_DIR}/stb.cpp 
${CMAKE_CURRENT_SOURCE_DIR}/tokenize.h 
${CMAKE_CURRENT_SOURCE_DIR}/tokenize.cpp
${CMAKE_CURRENT_SOURCE_DIR}/glad.c)

target_link_libraries(ProjectOrion glfw OpenGL::GL ${CMAKE_DL_LIBS}) 
target_link_libraries(ProjectOrion ${FREETYPE_LIBRARIES})
target_include_directories(ProjectOrion PUBLIC
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
                           $<INSTALL_INTERFACE:include>)
target_include_directories(ProjectOrion PRIVATE ${FREETYPE_INCLUDE_DIRS})


