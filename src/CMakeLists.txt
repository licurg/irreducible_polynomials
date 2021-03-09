cmake_minimum_required(VERSION 3.17)

set(HEADER "")
set(SOURCE "")

file(GLOB_RECURSE HEADER "${CMAKE_CURRENT_SOURCE_DIR}/../inc/*.h")

set(SOURCE
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/polynomial_generator.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/ui/main_window.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ui/wrapper.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ui/label.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ui/button.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ui/progress_bar.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ui/number_input.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} "../inc")

add_executable(${PROJECT_NAME} ${SOURCE} ${HEADER})

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})

set(DEBUG_SUFFIX)
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG)
    set(DEBUG_SUFFIX "d")
endif ()
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set_property(TARGET ${PROJECT_NAME} PROPERTY WIN32_EXECUTABLE true)
endif()

set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E make_directory
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
endif ()

foreach (QT_LIB ${REQUIRED_LIBS})
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            "${QT_INSTALL_PATH}/bin/Qt${QT_VERSION}${QT_LIB}${DEBUG_SUFFIX}.dll"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
endforeach (QT_LIB)
