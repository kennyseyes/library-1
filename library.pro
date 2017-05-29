#-------------------------------------------------
#
# Project created by QtCreator 2017-05-14T15:22:51
#
#-------------------------------------------------

QT       += core gui
QT       += core
QT       += network
QT       -= gui

TARGET = QDownloaderCLI

CONFIG   += console
CONFIG   -= app_bundle

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = library
TEMPLATE = app


SOURCES += main.cpp\
    login_adm_dialog.cpp \
    chose_login.cpp \
    login_user_dialog.cpp \
    a_mainwindow.cpp \
    u_mainwindow.cpp \
    change_password.cpp \
    borrow_book_form.cpp \
    book.cpp \
    user.cpp \
    showbookfound.cpp

HEADERS  += \
    login_adm_dialog.h \
    chose_login.h \
    login_user_dialog.h \
    a_mainwindow.h \
    u_mainwindow.h \
    change_password.h \
    borrow_book_form.h \
    user.h \
    book.h \
    showbookfound.h

FORMS    += \
    login_adm_dialog.ui \
    chose_login.ui \
    login_user_dialog.ui \
    a_mainwindow.ui \
    u_mainwindow.ui \
    change_password.ui \
    borrow_book_form.ui \
    showbookfound.ui
