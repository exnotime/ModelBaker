#-------------------------------------------------
#
# Project created by QtCreator 2015-07-26T10:55:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GL
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    modelloader.cpp \

HEADERS  += mainwindow.h \
    modelloader.h \
    Material.h \
    Model.h \
    Vertex.h \
    FileUtility.h

FORMS    += mainwindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lassimp
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -lassimpd
else:unix: LIBS += -L$$PWD/lib/ -lassimp

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/lib/libassimp.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/lib/libassimpd.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/lib/assimp.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/lib/assimpd.lib
else:unix: PRE_TARGETDEPS += $$PWD/lib/libassimp.a
