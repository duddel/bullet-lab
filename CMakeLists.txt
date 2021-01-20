cmake_minimum_required(VERSION 3.6)

project(bullet-lab)

enable_testing()
include(ExternalProject)

ExternalProject_Add(bullet-clone
  GIT_REPOSITORY https://github.com/bulletphysics/bullet3.git
  GIT_TAG 2.89
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
  GIT_SHALLOW ON
)

add_executable(${CMAKE_PROJECT_NAME}
  ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

add_dependencies(${CMAKE_PROJECT_NAME} bullet-clone)

# add the executable as a test to be run by ctest
add_test(
  NAME ${CMAKE_PROJECT_NAME}_run
  COMMAND ${CMAKE_PROJECT_NAME}
)
