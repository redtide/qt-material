QT             += core gui widgets
TEMPLATE        = app
CONFIG         += c++11
TARGET          = demo
INCLUDEPATH    += $$top_srcdir/include
INCLUDEPATH    += $$top_srcdir/src/library
LIBS           += $$top_builddir/src/library/$(OBJECTS_DIR)/src.a
PRE_TARGETDEPS += $$top_builddir/src/library/$(OBJECTS_DIR)/src.a

RESOURCES += resources/resources.qrc
SOURCES  = \
    main.cpp \
    mainwindow.cpp \
    avatarsettingseditor.cpp \
    badgesettingseditor.cpp \
    checkboxsettingseditor.cpp \
    fabsettingseditor.cpp \
    raisedbuttonsettingseditor.cpp \
    flatbuttonsettingseditor.cpp \
    iconbuttonsettingseditor.cpp \
    progresssettingseditor.cpp \
    circularprogresssettingseditor.cpp \
    slidersettingseditor.cpp \
    radiobuttonsettingseditor.cpp \
    togglesettingseditor.cpp \
    textfieldsettingseditor.cpp \
    tabssettingseditor.cpp \
    snackbarsettingseditor.cpp \
    dialogsettingseditor.cpp \
    drawersettingseditor.cpp \
    scrollbarsettingseditor.cpp \
    appbarsettingseditor.cpp \
    autocompletesettingseditor.cpp \
    menusettingseditor.cpp
HEADERS = \
    mainwindow.hpp \
    avatarsettingseditor.hpp \
    badgesettingseditor.hpp \
    checkboxsettingseditor.hpp \
    fabsettingseditor.hpp \
    raisedbuttonsettingseditor.hpp \
    flatbuttonsettingseditor.hpp \
    iconbuttonsettingseditor.hpp \
    progresssettingseditor.hpp \
    circularprogresssettingseditor.hpp \
    slidersettingseditor.hpp \
    radiobuttonsettingseditor.hpp \
    togglesettingseditor.hpp \
    textfieldsettingseditor.hpp \
    tabssettingseditor.hpp \
    snackbarsettingseditor.hpp \
    dialogsettingseditor.hpp \
    drawersettingseditor.hpp \
    scrollbarsettingseditor.hpp \
    appbarsettingseditor.hpp \
    autocompletesettingseditor.hpp \
    menusettingseditor.hpp
FORMS += \
    avatarsettingsform.ui \
    badgesettingsform.ui \
    checkboxsettingsform.ui \
    fabsettingsform.ui \
    flatbuttonsettingsform.ui \
    iconbuttonsettingsform.ui \
    progresssettingsform.ui \
    circularprogresssettingsform.ui \
    slidersettingsform.ui \
    snackbarsettingsform.ui \
    radiobuttonsettingsform.ui \
    togglesettingsform.ui \
    textfieldsettingsform.ui \ 
    tabssettingsform.ui \
    dialogsettingsform.ui \
    drawersettingsform.ui \
    scrollbarsettingsform.ui \
    appbarsettingsform.ui
