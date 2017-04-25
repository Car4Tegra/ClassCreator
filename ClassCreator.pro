#-------------------------------------------------
#
# Project created by QtCreator 2017-04-17T19:43:59
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ClassCreator
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(thirdparty/qtpropertybrowser/src/qtpropertybrowser.pri)


SOURCES += \
    source/classcreator.cpp \
    source/classtemplatexmlparser.cpp \
    source/configurationmanager.cpp \
    source/highlighter.cpp \
    source/main.cpp \
    source/mainwindow.cpp \
    source/preview.cpp \
    source/stringparser.cpp \
    source/usersettingsdialog.cpp \
    source/stringutil.cpp

HEADERS  += \
    include/basetoken.hpp \
    include/blocktoken.hpp \
    include/classcreator.hpp \
    include/classtemplatecommand.hpp \
    include/classtemplatedata.hpp \
    include/classtemplateproperty.hpp \
    include/classtemplatexmlparser.hpp \
    include/configurationmanager.hpp \
    include/highlighter.hpp \
    include/mainwindow.hpp \
    include/preview.hpp \
    include/stringparser.hpp \
    include/usersettingsdata.hpp \
    include/usersettingsdialog.hpp \
    include/stringutil.hpp

FORMS    += \
    resource/MainWindowView.ui \
    resource/PreviewView.ui \
    resource/UserSettingsDialogView.ui

RESOURCES += \
    resource/Icons.qrc

SUBDIRS +=

DISTFILES +=

INCLUDEPATH += include
INCLUDEPATH += thirdparty/qtpropertybrowser/src

templates.path    = $$OUT_PWD/templates
templates.files   = templates/*
INSTALLS += templates

CONFIG += c++14

QMAKE_CXXFLAGS -= -Wunused-parameter
