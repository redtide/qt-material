project(libqt-material-widgets
    VERSION ${CMAKE_PROJECT_VERSION}
    LANGUAGES CXX
)
# TODO: Install and translations

option(QT_MATERIAL_WIDGETS_BUILD_SHARED "Build as shared library [default: OFF]" OFF)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt${QT_MATERIAL_WIDGETS_QT_VERSION})
find_package(Qt${QT_VERSION_MAJOR} REQUIRED LinguistTools Widgets)

set(PROJECT_HEADERS
    ${CMAKE_SOURCE_DIR}/include/QtMaterialWidgets/appbar.hpp
    ${CMAKE_SOURCE_DIR}/include/QtMaterialWidgets/autocomplete.hpp
    ${CMAKE_SOURCE_DIR}/include/QtMaterialWidgets/avatar.hpp
    ${CMAKE_SOURCE_DIR}/include/QtMaterialWidgets/badge.hpp
    ${CMAKE_SOURCE_DIR}/include/QtMaterialWidgets/checkable.hpp
    ${CMAKE_SOURCE_DIR}/include/QtMaterialWidgets/checkbox.hpp
    ${CMAKE_SOURCE_DIR}/include/QtMaterialWidgets/circularprogress.hpp
    ${CMAKE_SOURCE_DIR}/include/QtMaterialWidgets/defs.hpp
    ${CMAKE_SOURCE_DIR}/include/QtMaterialWidgets/dialog.hpp
    ${CMAKE_SOURCE_DIR}/include/QtMaterialWidgets/dlimpexp.hpp
    ${CMAKE_SOURCE_DIR}/include/QtMaterialWidgets/drawer.hpp
    ${CMAKE_SOURCE_DIR}/include/QtMaterialWidgets/fab.hpp
    ${CMAKE_SOURCE_DIR}/include/QtMaterialWidgets/flatbutton.hpp
    ${CMAKE_SOURCE_DIR}/include/QtMaterialWidgets/iconbutton.hpp
    ${CMAKE_SOURCE_DIR}/include/QtMaterialWidgets/overlaywidget.hpp
    ${CMAKE_SOURCE_DIR}/include/QtMaterialWidgets/private/style_p.hpp # FIXME
    ${CMAKE_SOURCE_DIR}/include/QtMaterialWidgets/progress.hpp
    ${CMAKE_SOURCE_DIR}/include/QtMaterialWidgets/radiobutton.hpp
    ${CMAKE_SOURCE_DIR}/include/QtMaterialWidgets/raisedbutton.hpp
    ${CMAKE_SOURCE_DIR}/include/QtMaterialWidgets/ripple.hpp
    ${CMAKE_SOURCE_DIR}/include/QtMaterialWidgets/rippleoverlay.hpp
    ${CMAKE_SOURCE_DIR}/include/QtMaterialWidgets/scrollbar.hpp
    ${CMAKE_SOURCE_DIR}/include/QtMaterialWidgets/slider.hpp
    ${CMAKE_SOURCE_DIR}/include/QtMaterialWidgets/snackbar.hpp
    ${CMAKE_SOURCE_DIR}/include/QtMaterialWidgets/style.hpp
    ${CMAKE_SOURCE_DIR}/include/QtMaterialWidgets/switch.hpp
    ${CMAKE_SOURCE_DIR}/include/QtMaterialWidgets/tablayout.hpp
    ${CMAKE_SOURCE_DIR}/include/QtMaterialWidgets/tabs.hpp
    ${CMAKE_SOURCE_DIR}/include/QtMaterialWidgets/textfield.hpp
    ${CMAKE_SOURCE_DIR}/include/QtMaterialWidgets/theme.hpp
)
set(PROJECT_SOURCES
    appbar.cpp
    appbar_p.hpp
    autocomplete.cpp
    autocomplete_internal.cpp
    autocomplete_internal.hpp
    autocomplete_p.hpp
    avatar.cpp
    avatar_p.hpp
    badge.cpp
    badge_p.hpp
    checkable.cpp
    checkable_internal.cpp
    checkable_internal.hpp
    checkable_p.hpp
    checkbox.cpp
    checkbox_p.hpp
    circularprogress.cpp
    circularprogress_internal.cpp
    circularprogress_internal.hpp
    circularprogress_p.hpp
    dialog.cpp
    dialog_internal.cpp
    dialog_internal.hpp
    dialog_p.hpp
    drawer.cpp
    drawer_internal.cpp
    drawer_internal.hpp
    drawer_p.hpp
    fab.cpp
    fab_p.hpp
    flatbutton.cpp
    flatbutton_internal.cpp
    flatbutton_internal.hpp
    flatbutton_p.hpp
    iconbutton.cpp
    iconbutton_p.hpp
    overlaywidget.cpp
    progress.cpp
    progress_internal.cpp
    progress_internal.hpp
    progress_p.hpp
    radiobutton.cpp
    radiobutton_p.hpp
    raisedbutton.cpp
    raisedbutton_p.hpp
    ripple.cpp
    rippleoverlay.cpp
    scrollbar.cpp
    scrollbar_internal.cpp
    scrollbar_internal.hpp
    scrollbar_p.hpp
    slider.cpp
    slider_internal.cpp
    slider_internal.hpp
    slider_p.hpp
    snackbar.cpp
    snackbar_internal.cpp
    snackbar_internal.hpp
    snackbar_p.hpp
    statetransition.cpp
    statetransition.hpp
    statetransitionevent.hpp
    style.cpp
    switch.cpp
    switch_internal.cpp
    switch_internal.hpp
    switch_p.hpp
    tabs.cpp
    tabs_internal.cpp
    tabs_internal.hpp
    tabs_p.hpp
    tablayout.cpp
    textfield.cpp
    textfield_internal.cpp
    textfield_internal.hpp
    textfield_p.hpp
    theme.cpp
    theme_p.hpp
)
set(PROJECT_RESOURCES
    ${CMAKE_SOURCE_DIR}/resources/library/qtmaterialwidgets.qrc
)
if(false) # TODO: as system library
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(QT_MATERIAL_WIDGETS "qtmaterialwidgets" REQUIRED)
    add_library(qmw_system INTERFACE)
    target_include_directories(qmw_system INTERFACE ${QT_MATERIAL_WIDGETS_INCLUDE_DIRS})
    target_link_libraries(qmw_system INTERFACE ${QT_MATERIAL_WIDGETS_LIBRARIES})
    link_directories(${QT_MATERIAL_WIDGETS_LIBRARY_DIRS})
endif()

source_group("" FILES ${PROJECT_SOURCES})

if(QT_MATERIAL_WIDGETS_BUILD_SHARED)
    set(PROJECT_LIBRARY qmw_shared)
    add_library(qmw::shared ALIAS ${PROJECT_LIBRARY})
    add_library(${PROJECT_LIBRARY} SHARED ${PROJECT_HEADERS} ${PROJECT_SOURCES} ${PROJECT_RESOURCES})
    set_target_properties(PROJECT_LIBRARY PROPERTIES
        VERSION   "${PROJECT_VERSION}"
        SOVERSION "${PROJECT_VERSION_MAJOR}"
        PUBLIC_HEADER "${CMAKE_INSTALL_INCLUDEDIR}/QtMaterialWidgets"
    )
    install(TARGETS ${PROJECT_LIBRARY}
        LIBRARY       DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/QtMaterialWidgets"
    )
else()
    set(PROJECT_LIBRARY qmw_static)
    add_library(${PROJECT_LIBRARY} STATIC ${PROJECT_HEADERS} ${PROJECT_SOURCES} ${PROJECT_RESOURCES})
    add_library(qmw::static ALIAS ${PROJECT_LIBRARY})
endif()

set_target_properties(${PROJECT_LIBRARY} PROPERTIES
    OUTPUT_NAME qt-material-widgets
)
target_compile_definitions(${PROJECT_LIBRARY} PUBLIC QT_MATERIAL_LIBRARY)
target_include_directories(${PROJECT_LIBRARY} PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_LIBRARY} PRIVATE Qt::Widgets)
