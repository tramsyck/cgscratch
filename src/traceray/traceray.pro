QT -= gui

TEMPLATE = lib
CONFIG += staticlib

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(../common/common.pri)
message($${INCLUDEPATH})
SOURCES += \
    canvas.cpp \
    light.cpp \
    scene.cpp \
    tools.cpp \
    viewport.cpp

HEADERS += \
    canvas.h \
    light.h \
    scene.h \
    tools.h \
    viewport.h

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target
