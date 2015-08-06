#-------------------------------------------------
#
# Project created by QtCreator 2014-06-22T00:07:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport


TARGET = vs
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    controlthread.cpp \
    threadd.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    controlthread.h \
    threadd.h

FORMS    += mainwindow.ui





win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-vs-Desktop_Qt_5_3_0_MSVC2010_OpenGL_32bit-Release/lib/ -lopencv_core249
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-vs-Desktop_Qt_5_3_0_MSVC2010_OpenGL_32bit-Release/lib/ -lopencv_core249d
else:unix: LIBS += -L$$PWD/../build-vs-Desktop_Qt_5_3_0_MSVC2010_OpenGL_32bit-Release/lib/ -lopencv_core249

INCLUDEPATH += $$PWD/../build-vs-Desktop_Qt_5_3_0_MSVC2010_OpenGL_32bit-Release
DEPENDPATH += $$PWD/../build-vs-Desktop_Qt_5_3_0_MSVC2010_OpenGL_32bit-Release

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-vs-Desktop_Qt_5_3_0_MSVC2010_OpenGL_32bit-Release/lib/ -lopencv_highgui249
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-vs-Desktop_Qt_5_3_0_MSVC2010_OpenGL_32bit-Release/lib/ -lopencv_highgui249d
else:unix: LIBS += -L$$PWD/../build-vs-Desktop_Qt_5_3_0_MSVC2010_OpenGL_32bit-Release/lib/ -lopencv_highgui249

INCLUDEPATH += $$PWD/../build-vs-Desktop_Qt_5_3_0_MSVC2010_OpenGL_32bit-Release
DEPENDPATH += $$PWD/../build-vs-Desktop_Qt_5_3_0_MSVC2010_OpenGL_32bit-Release

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-vs-Desktop_Qt_5_3_0_MSVC2010_OpenGL_32bit-Release/lib/ -lopencv_imgproc249
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-vs-Desktop_Qt_5_3_0_MSVC2010_OpenGL_32bit-Release/lib/ -lopencv_imgproc249d
else:unix: LIBS += -L$$PWD/../build-vs-Desktop_Qt_5_3_0_MSVC2010_OpenGL_32bit-Release/lib/ -lopencv_imgproc249

INCLUDEPATH += $$PWD/../build-vs-Desktop_Qt_5_3_0_MSVC2010_OpenGL_32bit-Release
DEPENDPATH += $$PWD/../build-vs-Desktop_Qt_5_3_0_MSVC2010_OpenGL_32bit-Release

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../GapTest/lib/ -lopencv_core249
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../GapTest/lib/ -lopencv_core249d
else:unix: LIBS += -L$$PWD/../GapTest/lib/ -lopencv_core249

INCLUDEPATH += $$PWD/../GapTest
DEPENDPATH += $$PWD/../GapTest

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../GapTest/lib/ -lopencv_highgui249
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../GapTest/lib/ -lopencv_highgui249d
else:unix: LIBS += -L$$PWD/../GapTest/lib/ -lopencv_highgui249

INCLUDEPATH += $$PWD/../GapTest
DEPENDPATH += $$PWD/../GapTest

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../GapTest/lib/ -lopencv_imgproc249
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../GapTest/lib/ -lopencv_imgproc249d
else:unix: LIBS += -L$$PWD/../GapTest/lib/ -lopencv_imgproc249

INCLUDEPATH += $$PWD/../GapTest
DEPENDPATH += $$PWD/../GapTest


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-vs-Desktop_Qt_5_3_0_MSVC2010_OpenGL_32bit-Release (1)/lib/ -lopencv_imgproc249
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-vs-Desktop_Qt_5_3_0_MSVC2010_OpenGL_32bit-Release (1)/lib/ -lopencv_imgproc249d

INCLUDEPATH += $$PWD/../build-vs-Desktop_Qt_5_3_0_MSVC2010_OpenGL_32bit-Release (1)
DEPENDPATH += $$PWD/../build-vs-Desktop_Qt_5_3_0_MSVC2010_OpenGL_32bit-Release (1)

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../vc10/lib/ -lopencv_core249
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../vc10/lib/ -lopencv_core249d

INCLUDEPATH += $$PWD/../vc10
DEPENDPATH += $$PWD/../vc10

win32: LIBS += -L$$PWD/../vc10/lib/ -lopencv_highgui249

INCLUDEPATH += $$PWD/../vc10
DEPENDPATH += $$PWD/../vc10

win32: LIBS += -L$$PWD/../vc10/lib/ -lopencv_imgproc249

INCLUDEPATH += $$PWD/../vc10
DEPENDPATH += $$PWD/../vc10

win32: LIBS += -L$$PWD/../vc10/lib/ -lopencv_core249

INCLUDEPATH += $$PWD/../vc10
DEPENDPATH += $$PWD/../vc10
