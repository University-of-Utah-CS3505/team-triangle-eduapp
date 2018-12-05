#-------------------------------------------------
#
# Project created by QtCreator 2018-11-21T13:47:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = A8
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++1z

SOURCES += \
        main.cpp \
    pre_game_options.cpp \
    main_menu.cpp \
    boost_test.cpp \
    gameplay.cpp \
    textedit.cpp \
    engine.cpp \
    level_menu.cpp \
    tile.cpp \
    tank.cpp \
    cursor.cpp \
    level.cpp \
    bullet.cpp \
    object_def.cpp \
    gap_buffer.cpp

HEADERS += \
    pre_game_options.h \
    game_state.h \
    main_menu.h \
    gameplay.h \
    textedit.h \
    engine.h \
    level_menu.h \
    tile.h \
    tank.h \
    cursor.h \
    level.h \
    bullet.h \
    pyinqt.h \
    object_def.h \
    gap_buffer.h

FORMS += \
    pre_game_options.ui
#INCLUDEPATH += ../libs/Box2D
#LIBS += -L"../Box2D/Build/bin/x86_64/Debug/libBox2D.a
#LIBS += -lBox2D


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix:!macx: LIBS += -L$$PWD/libs/Box2D/Build/bin/x86_64/Debug/ -lBox2D

INCLUDEPATH += $$PWD/libs/Box2D
DEPENDPATH += $$PWD/libs/Box2D/Build/bin/x86_64/Debug

unix:!macx: PRE_TARGETDEPS += $$PWD/libs/Box2D/Build/bin/x86_64/Debug/libBox2D.a

LIBS += -L$$PWD/libs/SFML-2.5.1/lib/ -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system

INCLUDEPATH += $$PWD/libs/SFML-2.5.1/include
DEPENDPATH += $$PWD/libs/SFML-2.5.1/include

unix|win32: LIBS += -L$$PWD/libs/boost_1_67_0/stage/lib/ -lboost_python37 -lpython3.7m

INCLUDEPATH += $$PWD/libs/boost_1_67_0/stage
INCLUDEPATH += /usr/include/python3.7m
DEPENDPATH += $$PWD/libs/boost_1_67_0/stage

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/libs/boost_1_67_0/stage/lib/boost_python37.lib
else:unix|win32-g++: PRE_TARGETDEPS += $$PWD/libs/boost_1_67_0/stage/lib/libboost_python37.a
