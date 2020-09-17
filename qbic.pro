HEADERS     = src/pieceslist.h \
              src/prog.h \
              src/qbicmain.h \
			  src/wastebox.h
			  
RESOURCES   = src/qbic.qrc

SOURCES     = src/main.cpp \
              src/pieceslist.cpp \
			  src/prog.cpp \
              src/qbicmain.cpp \
			  src/wastebox.cpp

QMAKE_PROJECT_NAME = qbic



FORMS += src/qbicmain.ui \
    src/prog.ui
