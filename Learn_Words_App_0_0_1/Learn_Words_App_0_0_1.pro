QT       += core gui sql charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addword.cpp \
    common.cpp \
    deleteword.cpp \
    drawstatschart.cpp \
    listwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    setword.cpp \
    userlearns.cpp \
    userstats.cpp

HEADERS += \
    addword.h \
    common.h \
    deleteword.h \
    drawstatschart.h \
    listwidget.h \
    mainwindow.h \
    observer.h \
    setword.h \
    sizes.h \
    subject.h \
    userlearns.h \
    userstats.h

FORMS += \
    addword.ui \
    deleteword.ui \
    drawstatschart.ui \
    listwidget.ui \
    mainwindow.ui \
    setword.ui \
    userlearns.ui \
    userstats.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    all_resources.qrc

DISTFILES += \
    loading.gif
