cmake_minimum_required(VERSION 3.20)

set(CMAKE_TOOLCHAIN_FILE "C:/env/vcpkg/scripts/buildsystems/vcpkg.cmake")
set(CMAKE_CXX_STANDARD 20)
project(Tetris)

find_package(SFML COMPONENTS 
  system window graphics CONFIG REQUIRED)

file(GLOB SRC_FILES
  "${PROJECT_SOURCE_DIR}/src/*.hpp"
  "${PROJECT_SOURCE_DIR}/src/*.cpp")

add_executable(${CMAKE_PROJECT_NAME} ${SRC_FILES})

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE 
  sfml-system sfml-network sfml-graphics sfml-window)

# Copy 3 images
add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory 
  "${PROJECT_SOURCE_DIR}/images/"
  "$<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>/images")