QT += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = lib
#CONFIG+= staticlib
# Input
UI_DIR = ui
#LIBS+= -lqscintilla

HEADERS += \
    Plugin/PluginManager.h \
    Plugin/PluginInterface.h \
    MainWindow.h \
    ConfigManager.h \
    LogBrowser.h \
    LogBrowserDialog.h \
    Export.h \
    Core.h \
    Workspace/Workspace.h \
    Workspace/Dock.h \
    Workspace/Perspective.h \
    Plugin/PluginsDialog.h \
    Plugin/PluginItem.h \
    Plugin/PluginData.h

SOURCES += \
    Plugin/PluginManager.cpp \
    MainWindow.cpp \
    ConfigManager.cpp \
    LogBrowser.cpp \
    LogBrowserDialog.cpp \
    Core.cpp \
    Workspace/Workspace.cpp \
    Workspace/Perspective.cpp \
    Plugin/PluginsDialog.cpp \
    Plugin/PluginItem.cpp \
    Plugin/PluginData.cpp

DEFINES += CORE_LIBRARY


FORMS += \
    Plugin/PluginsDialog.ui \
    Plugin/PluginItem.ui

CONFIG(debug, debug|release) {
    DESTDIR = ../lib/debug
    OBJECTS_DIR = ../lib/debug/.obj
    MOC_DIR = ../lib/debug/.moc
    RCC_DIR = ../lib/debug/.rcc
} else {
    DESTDIR = ../lib/release
    OBJECTS_DIR = ../lib/release/.obj
    MOC_DIR = ../lib/release/.moc
    RCC_DIR = ../lib/release/.rcc
}

win32 {
    CONFIG(debug, debug|release) {
        LIB_FILES += ../lib/debug/Core.dll
    } else {
        LIB_FILES += ../lib/release/Core.dll
    }
}

unix {
    CONFIG(debug, debug|release) {
        LIB_FILES += ../lib/debug/libCore.so
    } else {
        LIB_FILES += ../lib/release/libCore.so
    }
}

## Define what files are 'extra_libs' and where to put them
extra_libs.files = $$LIB_FILES
extra_libs.path = $$DESTDIR

## Tell qmake to add the moving of them to the 'install' target
INSTALLS += extra_libs
