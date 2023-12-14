QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../back/credit_calc.c \
    ../back/data_validation.c \
    ../back/deposit_calc.c \
    ../back/stack.c \
    credit.cpp \
    deposit.cpp \
    form.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp

HEADERS += \
    ../back/data_validation.h \
    ../back/extra_calcs.h \
    ../back/stack.h \
    credit.h \
    deposit.h \
    form.h \
    mainwindow.h \
    qcustomplot.h

FORMS += \
    credit.ui \
    deposit.ui \
    form.ui \
    mainwindow.ui

ICON = ./rsrcs/calculator_icon.icns

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc \
    rsrcs/hello_puppy.qrc

