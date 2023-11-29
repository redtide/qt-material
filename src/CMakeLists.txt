add_subdirectory(library)

if(QT_MATERIAL_WIDGETS_BUILD_PLUGIN)
    add_subdirectory(designer)
endif()

if(QT_MATERIAL_WIDGETS_BUILD_DEMO)
    add_subdirectory(demo)
endif()
