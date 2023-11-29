cmake_minimum_required(VERSION 3.15)
project(demo LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(QT NAMES Qt${QT_MATERIAL_WIDGETS_QT_VERSION})
find_package(Qt${QT_VERSION_MAJOR} REQUIRED LinguistTools Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(PROJECT_SOURCES
    appbarsettingseditor.cpp
    appbarsettingseditor.hpp
    autocompletesettingseditor.cpp
    autocompletesettingseditor.hpp
    avatarsettingseditor.cpp
    avatarsettingseditor.hpp
    badgesettingseditor.cpp
    badgesettingseditor.hpp
    checkboxsettingseditor.cpp
    checkboxsettingseditor.hpp
    circularprogresssettingseditor.cpp
    circularprogresssettingseditor.hpp
    dialogsettingseditor.cpp
    dialogsettingseditor.hpp
    drawersettingseditor.cpp
    drawersettingseditor.hpp
    fabsettingseditor.cpp
    fabsettingseditor.hpp
    flatbuttonsettingseditor.cpp
    flatbuttonsettingseditor.hpp
    iconbuttonsettingseditor.cpp
    iconbuttonsettingseditor.hpp
    main.cpp
    demoform.cpp
    demoform.hpp
    mainwindow.cpp
    mainwindow.hpp
    progresssettingseditor.cpp
    progresssettingseditor.hpp
    radiobuttonsettingseditor.cpp
    radiobuttonsettingseditor.hpp
    raisedbuttonsettingseditor.cpp
    raisedbuttonsettingseditor.hpp
    scrollbarsettingseditor.cpp
    scrollbarsettingseditor.hpp
    slidersettingseditor.cpp
    slidersettingseditor.hpp
    snackbarsettingseditor.cpp
    snackbarsettingseditor.hpp
    switchsettingseditor.cpp
    switchsettingseditor.hpp
    tabssettingseditor.cpp
    tabssettingseditor.hpp
    textfieldsettingseditor.cpp
    textfieldsettingseditor.hpp
)
set(PROJECT_UI_FILES
    demoform.ui
    appbarsettingsform.ui
    avatarsettingsform.ui
    badgesettingsform.ui
    checkboxsettingsform.ui
    circularprogresssettingsform.ui
    dialogsettingsform.ui
    drawersettingsform.ui
    fabsettingsform.ui
    flatbuttonsettingsform.ui
    iconbuttonsettingsform.ui
    progresssettingsform.ui
    radiobuttonsettingsform.ui
    scrollbarsettingsform.ui
    slidersettingsform.ui
    snackbarsettingsform.ui
    switchsettingsform.ui
    tabssettingsform.ui
    textfieldsettingsform.ui
)
set(PROJECT_RESOURCES resources/resources.qrc)

source_group("" FILES ${PROJECT_SOURCES})
source_group("Resources" FILES ${PROJECT_RESOURCES})
source_group("UI" FILES ${PROJECT_UI_FILES})

if(ANDROID)
    add_library(${PROJECT_NAME} SHARED
        ${PROJECT_SOURCES}
        ${PROJECT_RESOURCES}
        ${PROJECT_UI_FILES}
    )
else()
    add_executable(${PROJECT_NAME}
        ${PROJECT_SOURCES}
        ${PROJECT_RESOURCES}
        ${PROJECT_UI_FILES}
    )
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
    qmw::static
    Qt::Widgets
)
