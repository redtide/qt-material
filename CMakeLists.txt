cmake_minimum_required (VERSION 3.19)
project(qt-material-widgets
    VERSION 0.2.0 LANGUAGES CXX
    DESCRIPTION "Qt custom widgets library for audio and mobile applications"
)
set(PROJECT_ORGANIZATION_NAME "qtilities")
set(PROJECT_ORGANIZATION_URL "${PROJECT_ORGANIZATION_NAME}.github.io")

option(QT_MATERIAL_WIDGETS_BUILD_DEMO                         "Whether to build the demo applications  [default: OFF]" OFF)
option(QT_MATERIAL_WIDGETS_BUILD_PLUGIN                       "Whether to build the QtDesigner plugin  [default: OFF]" OFF)
option(QT_MATERIAL_WIDGETS_TRANSLATIONS_UPDATE                "Update source translations              [default: OFF]" OFF)
option(QT_MATERIAL_WIDGETS_TRANSLATION_TEST_ENABLED           "Whether to enable translation testing   [default: OFF]" OFF)
set   (QT_MATERIAL_WIDGETS_TRANSLATION_TEST "it" CACHE STRING "Country code of language to test in IDE [default: it]")
set   (QT_MATERIAL_WIDGETS_QT_VERSION 5 CACHE STRING          "Qt version to use                       [default: 5]")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src)
add_subdirectory(include)
