cmake_minimum_required(VERSION 3.6)
include(ExternalProject)

ExternalProject_Add(bullet-clone
  GIT_REPOSITORY https://github.com/bulletphysics/bullet3.git
  GIT_TAG 2.89
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
  GIT_SHALLOW ON
)

ExternalProject_Get_property(bullet-clone SOURCE_DIR)

file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/BULLET_PHYSICS_SOURCE_DIR.cmake "set(BULLET_PHYSICS_SOURCE_DIR ${SOURCE_DIR})
")
