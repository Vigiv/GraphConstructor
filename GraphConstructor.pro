QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/File/file.cpp \
    src/Graph/edge.cpp \
    src/Graph/graphscene.cpp \
    src/Graph/topology.cpp \
    src/Graph/vertex.cpp \
    src/Matrix/cell.cpp \
    src/Matrix/matrix.cpp \
    src/Search/search.cpp \
    src/main.cpp \
    src/mainwindow.cpp

HEADERS += \
    src/File/file.h \
    src/Graph/edge.h \
    src/Graph/graphscene.h \
    src/Graph/topology.h \
    src/Graph/vertex.h \
    src/Matrix/cell.h \
    src/Matrix/matrix.h \
    src/Search/search.h \
    src/constants.h \
    src/mainwindow.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES +=

FORMS += \
    src/mainwindow.ui

DISTFILES +=
