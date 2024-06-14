QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

QMAKE_CXXFLAGS += -fpermissive -Wunused-parameter -Wunused-but-set-variable -Wunused-variable -Wreturn-type

ICON = icon.icns

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    bintree.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc


win32:RC_FILE = file.rc

DISTFILES += \
    icons/Ampeross-Qetto-2-Search.ico \
    icons/Custom-Icon-Design-Flatastic-8-Refresh.ico \
    icons/about.ico \
    icons/add.ico \
    icons/binary_tree.ico \
    icons/app.ico \
    icons/help.ico \
    icons/max_search.ico \
    icons/min_search.ico \
    icons/remove.ico \
    icons/search.ico \
    icons/tree.ico

