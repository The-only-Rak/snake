cmake_minimum_required(VERSION 3.15.0)
project(snake VERSION 0.1.0)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
#set(CMAKE_C_CPPCHECK "cppcheck")
include(CTest)
enable_testing()
file(GLOB SRC_FILES src/*.c src/*.h)
add_executable(snake main.c ${SRC_FILES})
target_include_directories(snake PUBLIC src)
find_package(SDL2 REQUIRED)
target_include_directories(snake PRIVATE ${SDL2_INCLUDE_DIR})
target_link_libraries(snake SDL2)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
