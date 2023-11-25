QT += core gui widgets
TEMPLATE = app
CONFIG += c++11
SOURCES = mainwindow.cpp \
    main.cpp \
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
HEADERS = mainwindow.hpp \
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
LIBS += $$top_builddir/components/$(OBJECTS_DIR)/libcomponents.a
INCLUDEPATH += $$top_srcdir/components/
INCLUDEPATH += $$top_srcdir/include

TARGET = examples-exe
PRE_TARGETDEPS += $$top_builddir/components/$(OBJECTS_DIR)/libcomponents.a

RESOURCES += \
    examples.qrc

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
