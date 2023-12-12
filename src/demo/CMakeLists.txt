cmake_minimum_required(VERSION 3.15)
project(demo LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(QT NAMES Qt${QT_MATERIAL_WIDGETS_QT_VERSION})
find_package(Qt${QT_VERSION_MAJOR} REQUIRED LinguistTools Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(PROJECT_SOURCES
    main.cpp
    MainWindow.cpp
    MainWindow.hpp
    AppBarSettings.cpp
    AppBarSettings.hpp
    AutoCompleteSettings.cpp
    AutoCompleteSettings.hpp
    AvatarSettings.cpp
    AvatarSettings.hpp
    BadgeSettings.cpp
    BadgeSettings.hpp
    CheckBoxSettings.cpp
    CheckBoxSettings.hpp
    CircularProgressSettings.cpp
    CircularProgressSettings.hpp
    DialogSettings.cpp
    DialogSettings.hpp
    DrawerSettings.cpp
    DrawerSettings.hpp
    FABSettings.cpp
    FABSettings.hpp
    FlatButtonSettings.cpp
    FlatButtonSettings.hpp
    IconButtonSettings.cpp
    IconButtonSettings.hpp
    ProgressSettings.cpp
    ProgressSettings.hpp
    RadioButtonSettings.cpp
    RadioButtonSettings.hpp
    RaisedButtonSettings.cpp
    RaisedButtonSettings.hpp
    ScrollBarSettings.cpp
    ScrollBarSettings.hpp
    SliderSettings.cpp
    SliderSettings.hpp
    SnackbarSettings.cpp
    SnackbarSettings.hpp
    SwitchSettings.cpp
    SwitchSettings.hpp
    TabsSettings.cpp
    TabsSettings.hpp
    TextFieldSettings.cpp
    TextFieldSettings.hpp
)
set(PROJECT_UI_FILES
    MainWindow.ui
    AppBarSettings.ui
    AutoCompleteSettings.ui
    AvatarSettings.ui
    BadgeSettings.ui
    CheckBoxSettings.ui
    CircularProgressSettings.ui
    DialogSettings.ui
    DrawerSettings.ui
    FABSettings.ui
    FlatButtonSettings.ui
    IconButtonSettings.ui
    ProgressSettings.ui
    RadioButtonSettings.ui
    RaisedButtonSettings.ui
    ScrollBarSettings.ui
    SliderSettings.ui
    SnackbarSettings.ui
    SwitchSettings.ui
    TabsSettings.ui
    TextFieldSettings.ui
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

set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_NAME md-demo-qt${QT_VERSION_MAJOR}
)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt::Widgets
    qmw::static
)
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})
endif()
