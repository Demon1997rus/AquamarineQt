cmake_minimum_required(VERSION 2.8.12)

project(AquamarineQt)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(LIBRARIES Qt5::Widgets)

add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${LIBRARIES})
