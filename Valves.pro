QT += quick # for get qml headers
CONFIG += lrelease
CONFIG += embed_translations

# QRC FILE
RESOURCES += qml.qrc

# SOURCE FILES
SOURCES += \
    src/columnvalvesviewmodel.cpp \
    src/main.cpp

# DIST FILES
DISTFILES += \
    qml/pages/main.qml \
    qml/components/TextButton.qml \
    assets/information.svg

HEADERS += \
    hdr/Types.h \
    hdr/columnvalvesviewmodel.h
