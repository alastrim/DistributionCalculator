SOURCES += \
    main.cpp \
    misc.cpp \
    distribution.cpp \
    chart_painter.cpp

HEADERS += \
    misc.h \
    distribution.h \
    chart_painter.h

QMAKE_CXXFLAGS += -llaspack -lxc -g -W -Wall -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -fstack-protector-all -Wfloat-equal -Wpointer-arith -Wwrite-strings -Wcast-align -Wno-long-long -Wmissing-declarations -lm -std=c++14
QMAKE_LFLAGS += -llaspack -lxc
LIBS += -llaspack -lxc
QT += charts
