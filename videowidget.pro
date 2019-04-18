# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Tools.
# ------------------------------------------------------

TEMPLATE = app
TARGET = videowidget
DESTDIR = ./debug
CONFIG += debug
DEFINES += _WINDOWS _UNICODE _ENABLE_EXTENDED_ALIGNED_STORAGE WIN64 QT_MULTIMEDIAWIDGETS_LIB QT_MULTIMEDIA_LIB QT_WIDGETS_LIB QT_NETWORK_LIB
INCLUDEPATH += ./GeneratedFiles/$(ConfigurationName) \
    ./GeneratedFiles \
    . \
    ./../QT/5.12.2/MSVC2017_64/include \
    ./../QT/5.12.2/MSVC2017_64/include/QtMultimediaWidgets \
    ./../QT/5.12.2/MSVC2017_64/include/QtMultimedia \
    ./../QT/5.12.2/MSVC2017_64/include/QtWidgets \
    ./../QT/5.12.2/MSVC2017_64/include/QtGui \
    ./../QT/5.12.2/MSVC2017_64/include/QtANGLE \
    ./../QT/5.12.2/MSVC2017_64/include/QtNetwork \
    ./../QT/5.12.2/MSVC2017_64/include/QtCore \
    ./tmp \
    ./../QT/5.12.2/MSVC2017_64/mkspecs/win32-msvc
DEPENDPATH += .
MOC_DIR += ./tmp
OBJECTS_DIR += debug
UI_DIR += .
RCC_DIR += $(Configuration)
include(videowidget.pri)

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../opencv/build/x64/vc14/lib/ -lopencv_world346
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../opencv/build/x64/vc14/lib/ -lopencv_world346d
else:unix: LIBS += -L$$PWD/../opencv/build/x64/vc14/lib/ -lopencv_world346

INCLUDEPATH += $$PWD/../opencv/build/x64/vc14
INCLUDEPATH += $$PWD/../opencv/build/include/opencv
INCLUDEPATH += $$PWD/../opencv/build/include
INCLUDEPATH += $$PWD/../opencv/build/include/opencv2
DEPENDPATH += $$PWD/../opencv/build/x64/vc14
