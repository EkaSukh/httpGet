TEMPLATE      = app
QT            += core network gui qml quick charts
CONFIG       += console qtquickcompiler

CONFIG       -= app_bundle
HEADERS       = httpget.h
SOURCES       = httpget.cpp \
    main.cpp

DISTFILES +=

RESOURCES += \
    main.qrc
