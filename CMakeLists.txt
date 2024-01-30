cmake_minimum_required(VERSION 3.14)

SET(PROJ_NAME "Game")
project(${PROJ_NAME})

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

file(GLOB GAME Game/*.cpp Game/*.h)
file(GLOB ENGINE Engine3D/*.cpp Engine3D/*.c  Engine3D/*.h)
file(GLOB DISPLAY DisplayGLFW/*.cpp DisplayGLFW/*.h)

include_directories(${PROJECT_SOURCE_DIR}/res/includes ${PROJECT_SOURCE_DIR}/Engine3D
 ${PROJECT_SOURCE_DIR}/DisplayGLFW)
add_subdirectory(${PROJECT_SOURCE_DIR}/res/includes/glfw)
add_subdirectory(${PROJECT_SOURCE_DIR}/res/includes/glad)


add_library(Display ${DISPLAY}
        Util/Reader/ConfigReader.cpp
        Util/Reader/ConfigReader.h
        Util/Light/Light.cpp
        Util/Light/Light.h
        Util/Light/SpotLight.h
        Util/Light/DirectionalLight.cpp
        Util/Light/DirectionalLight.h
        Util/Object/Object.cpp
        Util/Object/Object.h
        Util/Object/Plane.cpp
        Util/Object/Plane.h
        Util/Object/Sphere.cpp
        Util/Object/Sphere.h
        Util/ImageConstractor/Image.h
        Util/ImageConstractor/Image.cpp
        Util/ImageConstractor/Image.cpp
        Util/ImageConstractor/Ray.cpp
        Util/ImageConstractor/Ray.h
        Util/ImageConstractor/Hit.cpp
        Util/ImageConstractor/Hit.h)
add_library(Engine ${ENGINE})


add_executable(${PROJ_NAME} ${GAME})

target_link_libraries(${PROJ_NAME} Engine Display glfw glad)

