#-------------------------------------------------
#
# Project created by QtCreator 2015-12-09T16:45:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = CSVReader
TEMPLATE = app

SOURCES += main.cpp\
        csvreadermainwindow.cpp \     
    csvreader.cpp \
    csvtablerepresentation.cpp \
    csvmodel.cpp \
    comboboxdelegate.cpp \
    spinboxdelegate.cpp \
    textboxdelegate.cpp \
    addcolumndialog.cpp

HEADERS  += csvreadermainwindow.h \     
    csvreader.h \
    csvtablerepresentation.h \
    csvmodel.h \
    comboboxdelegate.h \
    spinboxdelegate.h \
    textboxdelegate.h \
    addcolumndialog.h

FORMS    += csvreadermainwindow.ui \
    csvreader.ui \
    addcolumndialog.ui
