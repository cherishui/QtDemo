QT       += core gui

QT += concurrent
QT += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

QMAKE_PROJECT_DEPTH = 0

CONFIG += console

message(CONFIG: $$CONFIG)

# MSVC 统一配置
msvc {
    QMAKE_CXXFLAGS += /utf-8
    QMAKE_CFLAGS += /utf-8
    # 关键：Debug 模式也强制使用多线程 DLL（/MDd 默认可能有问题）
    QMAKE_CXXFLAGS_DEBUG -= /MTd
    QMAKE_CXXFLAGS_DEBUG += /MDd
}

# MinGW 统一配置
gcc {
    QMAKE_CXXFLAGS += -fexec-charset=UTF-8
}
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    MyButton.cpp \
    ScrollBarStyleGenerator.cpp \
    WorkThread.cpp \
    main.cpp \
    mainwindow.cpp \
    qtestscrollarea.cpp

HEADERS += \
    MyButton.h \
    ScrollBarStyleGenerator.h \
    WorkThread.h \
    mainwindow.h \
    qtestscrollarea.h

FORMS += \
    mainwindow.ui \
    qtestscrollarea.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
