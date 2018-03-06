TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    balancing.cpp \
    stack.cpp

HEADERS += \
    stack.hpp

DISTFILES += \
    input_balanced.txt
