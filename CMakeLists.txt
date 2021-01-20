cmake_minimum_required(VERSION 3.6)

project(bullet-lab)

enable_testing()

# the following procedure clones the bullet repo before this instance
# of CMake continues, so it can be used (via add_subdirectory()) below.
# step 1: copy the CMake script
configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/bullet-clone.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/bullet-clone/CMakeLists.txt" COPYONLY
)
# step 2: run the script in a separate CMake instance
execute_process(
  COMMAND "${CMAKE_COMMAND}" .
  RESULT_VARIABLE bulletCloneResult
  WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bullet-clone"
)
if(bulletCloneResult)
  message(FATAL_ERROR "Configure step of bullet-clone FAILED: ${bulletCloneResult}")
endif()
# step 3: run the "build step" in a separate CMake instance
execute_process(
  COMMAND "${CMAKE_COMMAND}" --build .
  RESULT_VARIABLE bulletCloneResult
  WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bullet-clone"
)
if(bulletCloneResult)
  message(FATAL_ERROR "Build step of bullet-clone FAILED: ${bulletCloneResult}")
endif()
# step 4: include the generated file, that sets BULLET_PHYSICS_SOURCE_DIR
include(${CMAKE_CURRENT_BINARY_DIR}/bullet-clone/BULLET_PHYSICS_SOURCE_DIR.cmake)


set(BULLET_VERSION 2.89)
add_subdirectory(${BULLET_PHYSICS_SOURCE_DIR}/src/BulletInverseDynamics)
add_subdirectory(${BULLET_PHYSICS_SOURCE_DIR}/src/BulletSoftBody)
add_subdirectory(${BULLET_PHYSICS_SOURCE_DIR}/src/BulletCollision)
add_subdirectory(${BULLET_PHYSICS_SOURCE_DIR}/src/BulletDynamics)
add_subdirectory(${BULLET_PHYSICS_SOURCE_DIR}/src/LinearMath)
add_subdirectory(${BULLET_PHYSICS_SOURCE_DIR}/src/Bullet3Common)

add_executable(${CMAKE_PROJECT_NAME}
  ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${BULLET_PHYSICS_SOURCE_DIR}/src
)

target_link_libraries(${CMAKE_PROJECT_NAME}
  BulletInverseDynamics
  BulletSoftBody
  BulletDynamics
  BulletCollision
  LinearMath
  Bullet3Common
)

# add the executable as a test to be run by ctest
add_test(
  NAME ${CMAKE_PROJECT_NAME}_run
  COMMAND ${CMAKE_PROJECT_NAME}
)
