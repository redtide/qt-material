cmake_minimum_required(VERSION 3.15)
project(demo LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.
#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.hpp
)
set(PROJECT_RESOURCES resources/resources.qrc)

source_group("Sources" FILES ${PROJECT_SOURCES})
source_group("Resources" FILES ${PROJECT_RESOURCES})

if(ANDROID)
    add_library(${PROJECT_NAME} SHARED
        ${PROJECT_SOURCES}
        ${PROJECT_RESOURCES}
    )
else()
    add_executable(${PROJECT_NAME}
        ${PROJECT_SOURCES}
        ${PROJECT_RESOURCES}
    )
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
  Qt::Widgets
  qmw::static
)
