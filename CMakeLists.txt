cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(composite LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

find_package(GTest REQUIRED)
enable_testing()

add_executable(${PROJECT_NAME}_spec src/composite.cpp)
target_include_directories(
  ${PROJECT_NAME}_spec SYSTEM
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
         $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDE}> ${GTEST_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME}_spec PUBLIC ${GTEST_LIBRARIES})

install(TARGETS ${PROJECT_NAME}_spec DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
install(FILES src/test.json DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
