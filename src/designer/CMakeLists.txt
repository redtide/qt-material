project(qt-material-plugin
    VERSION ${CMAKE_PROJECT_VERSION}
    LANGUAGES CXX
)
find_package(QT NAMES Qt${QT_MATERIAL_WIDGETS_QT_VERSION})
if(${QT_VERSION_MAJOR} EQUAL 6)
    find_package(Qt${QT_VERSION_MAJOR} REQUIRED Core Designer Gui Widgets)
else()
    find_package(Qt${QT_VERSION_MAJOR} REQUIRED Core UiPlugin Widgets)
endif()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(PROJECT_SOURCES
    plugin.cpp
    plugin.hpp
    tablayoutcontainerextension.cpp
    tablayoutcontainerextension.hpp
    tablayoutextensionfactory.cpp
    tablayoutextensionfactory.hpp
)
set(PROJECT_RESOURCES
    ${CMAKE_SOURCE_DIR}/resources/designer/material-plugin.qrc
)
source_group("" FILES ${PROJECT_SOURCES})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_add_plugin(${PROJECT_NAME} SHARED MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${PROJECT_RESOURCES}
    )
    target_link_libraries(${PROJECT_NAME} PUBLIC
        Qt::Core
        Qt::Designer
        Qt::Gui
        Qt::Widgets
    )
else()
    add_library(${PROJECT_NAME} SHARED
        ${PROJECT_SOURCES}
        ${PROJECT_RESOURCES}
    )
target_link_libraries(${PROJECT_NAME} PUBLIC
        Qt::Core
        Qt::Widgets
        Qt::UiPlugin
    )
endif()

add_library(qmw::plugin ALIAS ${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_NAME qt${QT_VERSION_MAJOR}-material-widgets-plugin
)
if(PROJECT_BUILD_SHARED)
    target_link_libraries(${PROJECT_NAME} PRIVATE qmw::shared)
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE qmw::static)
endif()
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

set(PLUGIN_INSTALL_DIR "${QT${QT_VERSION_MAJOR}_INSTALL_PREFIX}/${QT${QT_VERSION_MAJOR}_INSTALL_PLUGINS}/designer")

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION "${PLUGIN_INSTALL_DIR}"
    LIBRARY DESTINATION "${PLUGIN_INSTALL_DIR}"
    BUNDLE DESTINATION  "${PLUGIN_INSTALL_DIR}"
)
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_target(${PROJECT_NAME})
endif()
