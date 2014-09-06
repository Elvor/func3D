TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lGLU -lGLEW -lsfml-system -lsfml-window -lsfml-graphics -lGL

SOURCES += main.cpp \
    FDrawer.cpp

HEADERS += \
    FDrawer.hpp

