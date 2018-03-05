TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    stack.cpp \
    postfixeval.cpp \
    infix2postfix.cpp \
    balancing.cpp

HEADERS += \
    stack.hpp

DISTFILES += \
    input_balanced.txt \
    input_infix2postfix.txt \
    input_postfixEval.txt
