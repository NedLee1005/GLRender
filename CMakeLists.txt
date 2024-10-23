cmake_minimum_required(VERSION 3.16)

set(EXE gl_render)
project(${EXE} C CXX)

find_package(OpenCV REQUIRED)

find_package(Threads REQUIRED)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17" )
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

aux_source_directory(./src/ SRC_LIST)
aux_source_directory(./shader_c/ REF_LIST)
include_directories(
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/include
        ${OpenCV_INCLUDE_DIRS}
)

add_executable(${EXE} ${SRC_LIST} ${REF_LIST})

target_link_libraries(
${EXE}
${OpenCV_LIBS} 
-ldl 
-lpthread 
-ldrm 
-lGLESv2 
-lVDK 
-lEGL 
)
