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

# 使用 Edit and Continue 调试信息
      QMAKE_CXXFLAGS_DEBUG += /ZI
      QMAKE_CFLAGS_DEBUG += /ZI

      # 去掉普通调试信息
      QMAKE_CXXFLAGS_DEBUG -= /Zi
      QMAKE_CFLAGS_DEBUG -= /Zi

      # 禁止优化
      QMAKE_CXXFLAGS_DEBUG += /Od
      QMAKE_CFLAGS_DEBUG += /Od

      # 启用增量链接
      QMAKE_LFLAGS_DEBUG += /INCREMENTAL /DEBUG

      # 去掉冲突设置
      QMAKE_LFLAGS_DEBUG -= /SAFESEH
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
    WorkThread.cpp \
    cmycombox.cpp \
    cmydateedit.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    MyButton.h \
    WorkThread.h \
    cmycombox.h \
    cmydateedit.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
