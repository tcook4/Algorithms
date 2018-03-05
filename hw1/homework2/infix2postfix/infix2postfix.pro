TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    infix2postfix.cpp \
    stack.cpp

HEADERS += \
    stack.hpp

DISTFILES += \
    input_infix2postfix.txt
