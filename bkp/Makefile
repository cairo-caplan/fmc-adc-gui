#############################################################################
# Makefile for building: fmc-adc-gui
# Generated by qmake (2.01a) (Qt 4.8.7) on: qui out 20 16:22:44 2016
# Project:  fmc-adc-gui.pro
# Template: app
# Command: /usr/lib/x86_64-linux-gnu/qt4/bin/qmake -spec /usr/share/qt4/mkspecs/linux-g++-64 -o Makefile fmc-adc-gui.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -m64 -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -m64 -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++-64 -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I/usr/include/root -I. -I.
LINK          = g++
LFLAGS        = -m64 -Wl,-O1
LIBS          = $(SUBLIBS)  -L/usr/lib/x86_64-linux-gnu -L/usr/lib64/root -lCore -lCint -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lGui -lRGL -lQtGui -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/lib/x86_64-linux-gnu/qt4/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = main.cpp \
		mainwindow.cpp \
		qmaincanvas.cpp \
		qrootcanvas.cpp \
		aboutwindow.cpp \
		frmsettings.cpp \
		daqmodule.cpp \
		vxtrootcanvas.cpp moc_mainwindow.cpp \
		moc_qmaincanvas.cpp \
		moc_qrootcanvas.cpp \
		moc_aboutwindow.cpp \
		moc_frmsettings.cpp \
		moc_daqmodule.cpp \
		moc_vxtrootcanvas.cpp \
		qrc_resources.cpp
OBJECTS       = main.o \
		mainwindow.o \
		qmaincanvas.o \
		qrootcanvas.o \
		aboutwindow.o \
		frmsettings.o \
		daqmodule.o \
		vxtrootcanvas.o \
		moc_mainwindow.o \
		moc_qmaincanvas.o \
		moc_qrootcanvas.o \
		moc_aboutwindow.o \
		moc_frmsettings.o \
		moc_daqmodule.o \
		moc_vxtrootcanvas.o \
		qrc_resources.o
DIST          = /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/shared.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		fmc-adc-gui.pro
QMAKE_TARGET  = fmc-adc-gui
DESTDIR       = 
TARGET        = fmc-adc-gui

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET): ui_mainwindow.h ui_aboutwindow.h ui_frmsettings.h $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: fmc-adc-gui.pro  /usr/share/qt4/mkspecs/linux-g++-64/qmake.conf /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/shared.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/x86_64-linux-gnu/libQtGui.prl \
		/usr/lib/x86_64-linux-gnu/libQtCore.prl
	$(QMAKE) -spec /usr/share/qt4/mkspecs/linux-g++-64 -o Makefile fmc-adc-gui.pro
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/common/gcc-base.conf:
/usr/share/qt4/mkspecs/common/gcc-base-unix.conf:
/usr/share/qt4/mkspecs/common/g++-base.conf:
/usr/share/qt4/mkspecs/common/g++-unix.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/release.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/shared.prf:
/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/x86_64-linux-gnu/libQtGui.prl:
/usr/lib/x86_64-linux-gnu/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -spec /usr/share/qt4/mkspecs/linux-g++-64 -o Makefile fmc-adc-gui.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/fmc-adc-gui1.0.0 || $(MKDIR) .tmp/fmc-adc-gui1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/fmc-adc-gui1.0.0/ && $(COPY_FILE) --parents mainwindow.h qmaincanvas.h qrootcanvas.h aboutwindow.h frmsettings.h daqmodule.h vxtrootcanvas.h acq_types.h .tmp/fmc-adc-gui1.0.0/ && $(COPY_FILE) --parents resources.qrc .tmp/fmc-adc-gui1.0.0/ && $(COPY_FILE) --parents main.cpp mainwindow.cpp qmaincanvas.cpp qrootcanvas.cpp aboutwindow.cpp frmsettings.cpp daqmodule.cpp vxtrootcanvas.cpp .tmp/fmc-adc-gui1.0.0/ && $(COPY_FILE) --parents mainwindow.ui aboutwindow.ui frmsettings.ui .tmp/fmc-adc-gui1.0.0/ && (cd `dirname .tmp/fmc-adc-gui1.0.0` && $(TAR) fmc-adc-gui1.0.0.tar fmc-adc-gui1.0.0 && $(COMPRESS) fmc-adc-gui1.0.0.tar) && $(MOVE) `dirname .tmp/fmc-adc-gui1.0.0`/fmc-adc-gui1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/fmc-adc-gui1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_mainwindow.cpp moc_qmaincanvas.cpp moc_qrootcanvas.cpp moc_aboutwindow.cpp moc_frmsettings.cpp moc_daqmodule.cpp moc_vxtrootcanvas.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_mainwindow.cpp moc_qmaincanvas.cpp moc_qrootcanvas.cpp moc_aboutwindow.cpp moc_frmsettings.cpp moc_daqmodule.cpp moc_vxtrootcanvas.cpp
moc_mainwindow.cpp: qmaincanvas.h \
		qrootcanvas.h \
		vxtrootcanvas.h \
		acq_types.h \
		aboutwindow.h \
		frmsettings.h \
		daqmodule.h \
		mainwindow.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) mainwindow.h -o moc_mainwindow.cpp

moc_qmaincanvas.cpp: qrootcanvas.h \
		qmaincanvas.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) qmaincanvas.h -o moc_qmaincanvas.cpp

moc_qrootcanvas.cpp: qrootcanvas.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) qrootcanvas.h -o moc_qrootcanvas.cpp

moc_aboutwindow.cpp: aboutwindow.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) aboutwindow.h -o moc_aboutwindow.cpp

moc_frmsettings.cpp: daqmodule.h \
		acq_types.h \
		frmsettings.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) frmsettings.h -o moc_frmsettings.cpp

moc_daqmodule.cpp: acq_types.h \
		daqmodule.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) daqmodule.h -o moc_daqmodule.cpp

moc_vxtrootcanvas.cpp: acq_types.h \
		qrootcanvas.h \
		vxtrootcanvas.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) vxtrootcanvas.h -o moc_vxtrootcanvas.cpp

compiler_rcc_make_all: qrc_resources.cpp
compiler_rcc_clean:
	-$(DEL_FILE) qrc_resources.cpp
qrc_resources.cpp: resources.qrc \
		imgs/Open-source-hardware-logo.svg.png \
		imgs/ohr_logo_240x320_image.png \
		imgs/FallingEdge.png \
		imgs/RisingEdge.png \
		imgs/CERN-logo.jpg \
		imgs/120px-True_icon.svg.png \
		imgs/cbpf.jpeg \
		imgs/BothEdges.png \
		imgs/TriggerEdge.png \
		imgs/120px-False_icon.svg.png
	/usr/lib/x86_64-linux-gnu/qt4/bin/rcc -name resources resources.qrc -o qrc_resources.cpp

compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: ui_mainwindow.h ui_aboutwindow.h ui_frmsettings.h
compiler_uic_clean:
	-$(DEL_FILE) ui_mainwindow.h ui_aboutwindow.h ui_frmsettings.h
ui_mainwindow.h: mainwindow.ui
	/usr/lib/x86_64-linux-gnu/qt4/bin/uic mainwindow.ui -o ui_mainwindow.h

ui_aboutwindow.h: aboutwindow.ui
	/usr/lib/x86_64-linux-gnu/qt4/bin/uic aboutwindow.ui -o ui_aboutwindow.h

ui_frmsettings.h: frmsettings.ui
	/usr/lib/x86_64-linux-gnu/qt4/bin/uic frmsettings.ui -o ui_frmsettings.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_rcc_clean compiler_uic_clean 

####### Compile

main.o: main.cpp mainwindow.h \
		qmaincanvas.h \
		qrootcanvas.h \
		vxtrootcanvas.h \
		acq_types.h \
		aboutwindow.h \
		frmsettings.h \
		daqmodule.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

mainwindow.o: mainwindow.cpp mainwindow.h \
		qmaincanvas.h \
		qrootcanvas.h \
		vxtrootcanvas.h \
		acq_types.h \
		aboutwindow.h \
		frmsettings.h \
		daqmodule.h \
		ui_mainwindow.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o mainwindow.o mainwindow.cpp

qmaincanvas.o: qmaincanvas.cpp qmaincanvas.h \
		qrootcanvas.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qmaincanvas.o qmaincanvas.cpp

qrootcanvas.o: qrootcanvas.cpp qrootcanvas.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qrootcanvas.o qrootcanvas.cpp

aboutwindow.o: aboutwindow.cpp aboutwindow.h \
		ui_aboutwindow.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o aboutwindow.o aboutwindow.cpp

frmsettings.o: frmsettings.cpp frmsettings.h \
		daqmodule.h \
		acq_types.h \
		ui_frmsettings.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o frmsettings.o frmsettings.cpp

daqmodule.o: daqmodule.cpp daqmodule.h \
		acq_types.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o daqmodule.o daqmodule.cpp

vxtrootcanvas.o: vxtrootcanvas.cpp vxtrootcanvas.h \
		acq_types.h \
		qrootcanvas.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o vxtrootcanvas.o vxtrootcanvas.cpp

moc_mainwindow.o: moc_mainwindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_mainwindow.o moc_mainwindow.cpp

moc_qmaincanvas.o: moc_qmaincanvas.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_qmaincanvas.o moc_qmaincanvas.cpp

moc_qrootcanvas.o: moc_qrootcanvas.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_qrootcanvas.o moc_qrootcanvas.cpp

moc_aboutwindow.o: moc_aboutwindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_aboutwindow.o moc_aboutwindow.cpp

moc_frmsettings.o: moc_frmsettings.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_frmsettings.o moc_frmsettings.cpp

moc_daqmodule.o: moc_daqmodule.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_daqmodule.o moc_daqmodule.cpp

moc_vxtrootcanvas.o: moc_vxtrootcanvas.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_vxtrootcanvas.o moc_vxtrootcanvas.cpp

qrc_resources.o: qrc_resources.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qrc_resources.o qrc_resources.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

