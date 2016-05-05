#-------------------------------------------------
#
# Project created by QtCreator 2016-04-22T23:42:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = fmc-adc-gui
TEMPLATE = app

#INCLUDEPATH += $(ROOTSYS)/include
INCLUDEPATH += /usr/include/root
win32:LIBS += -L$(ROOTSYS)/lib -llibCore -llibCint -llibRIO -llibNet \
        -llibHist -llibGraf -llibGraf3d -llibGpad -llibTree \
        -llibRint -llibPostscript -llibMatrix -llibPhysics \
        -llibGui -llibRGL
#else:LIBS += -L$(ROOTSYS)/lib -lCore -lCint -lRIO -lNet \
else:LIBS += -L"/usr/lib64/root" -lCore -lCint -lRIO -lNet \
        -lHist -lGraf -lGraf3d -lGpad -lTree \
        -lRint -lPostscript -lMatrix -lPhysics \
        -lGui -lRGL


SOURCES += main.cpp\
        mainwindow.cpp \
    qmaincanvas.cpp \
    qrootcanvas.cpp \
    aboutwindow.cpp \
    frmsettings.cpp \
    daqmodule.cpp \
    vxtrootcanvas.cpp

HEADERS  += mainwindow.h \
    qmaincanvas.h \
    qrootcanvas.h \
    aboutwindow.h \
    frmsettings.h \
    daqmodule.h \
    vxtrootcanvas.h

FORMS    += mainwindow.ui \
    aboutwindow.ui \
    frmsettings.ui

RESOURCES += \
    resources.qrc
