SOURCES += \
    dnd_dice.cpp \
    main.cpp \
    misc.cpp \
    distribution.cpp \
    chart_painter.cpp \
    distribution_function.cpp \
    stats.cpp \
    target_function.cpp \
    modifiers.cpp \
    tests.cpp

HEADERS += \
    dnd_dice.h \
    misc.h \
    distribution.h \
    chart_painter.h \
    distribution_function.h \
    stats.h \
    target_function.h \
    modifiers.h \
    tests.h

QMAKE_CXXFLAGS += -g -W -Wall -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -fstack-protector-all -Wfloat-equal -Wpointer-arith -Wwrite-strings -Wcast-align -Wno-long-long -Wmissing-declarations -lm -std=c++14
QMAKE_CXXFLAGS += -O3 -ffast-math
#QMAKE_CXXFLAGS += -O0
CONFIG += console
win32 {
  LIBS += -lssp
}
