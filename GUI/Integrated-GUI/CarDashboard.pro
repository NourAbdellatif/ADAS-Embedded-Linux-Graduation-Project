QT       += core gui network widgets

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    customerdialog.cpp \
    main.cpp \
    mainwindow.cpp \
    processthread.cpp \
    progdialog.cpp \
    logindialog.cpp \
    passdialog.cpp \
    bugreportingdialog.cpp

HEADERS += \
    customerdialog.h \
    mainwindow.h \
    preprocessing.h \
    processthread.h \
    progdialog.h \
    logindialog.h \
    passdialog.h \
    bugreportingdialog.h

FORMS += \
    customerdialog.ui \
    mainwindow.ui \
    progdialog.ui \
    logindialog.ui \
    passdialog.ui \
    bugreportingdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc

DISTFILES += \
    CMakeLists.txt \
    CMakeLists.txt.user \
    CarDashboard.pro.user \
    License.txt \
    README.md

LIBS += -lssl -lcrypto

PKGCONFIG += openssl
