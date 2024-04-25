QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addoneword.cpp \
    common.cpp \
    deleteoneword.cpp \
    main.cpp \
    mainwindow.cpp \
    setword.cpp \
    usersession.cpp

HEADERS += \
    addoneword.h \
    all_sizes.h \
    common.h \
    deleteoneword.h \
    mainwindow.h \
    setword.h \
    usersession.h

FORMS += \
    addoneword.ui \
    deleteoneword.ui \
    mainwindow.ui \
    setword.ui \
    usersession.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
