QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../back/data_validation.c \
    ../back/stack.c \
    main.cpp \
    mainwindow.cpp \

HEADERS += \
    ../back/data_validation.h \
    ../back/stack.h \
    mainwindow.h \

FORMS += \
    mainwindow.ui

ICON = ./calculator_icon.icns

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    hello_puppy.qrc \
    icons.qrc
