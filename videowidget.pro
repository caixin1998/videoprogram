TEMPLATE = app
TARGET = videowidget

QT += multimedia multimediawidgets

HEADERS = \
    videoplayer.h \
    showimage.h \
    videosurface.h \
    customslider.h \
    minorscreen.h \
    mainwindow.h \
    camerathread.h \
    cameraplayer.h \
    rotateimage.h

SOURCES = \
    main.cpp \
    videoplayer.cpp \
    showimage.cpp \
    videosurface.cpp \
    customslider.cpp \
    minorscreen.cpp \
    mainwindow.cpp \
    camerathread.cpp \
    cameraplayer.cpp \
    rotateimage.cpp

target.path = $$[QT_INSTALL_EXAMPLES]/multimediawidgets/videowidget
INSTALLS += target

QT+=widgets

FORMS += \
    minorscreen.ui \
    mainwindow.ui

RESOURCES += \
    cover.qrc

OBJECTS_DIR  = tmp
MOC_DIR      = tmp
