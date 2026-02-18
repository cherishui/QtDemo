#if defined(_MSC_VER)
#pragma execution_character_set("utf-8")
#endif

#include <QApplication>
#include <QDebug>
#include "mainwindow.h"

#ifdef Q_OS_WIN
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#endif

// 强制 UTF-8 输出
void setupUtf8Output()
{
#ifdef Q_OS_WIN
    // 设置控制台为 UTF-8
    SetConsoleOutputCP(CP_UTF8);

    // 关键：设置 stdout/stderr 为 UTF-8 模式
    _setmode(_fileno(stdout), _O_U8TEXT);
    _setmode(_fileno(stderr), _O_U8TEXT);
#endif
}

// 自定义消息处理器 - 完全绕过 C 运行时
void utf8MessageHandler(QtMsgType type, const QMessageLogContext &context,
                        const QString &msg)
{
    Q_UNUSED(context);
    //Q_UNUSED();

#ifdef Q_OS_WIN
    // 转换为 UTF-16（Windows 原生）
    std::wstring wmsg = msg.toStdWString();

    // 使用 WriteConsoleW 直接输出（绝对不乱码）
    HANDLE hStdErr = GetStdHandle(STD_ERROR_HANDLE);
    DWORD written;

    switch (type) {
    case QtDebugMsg:
        WriteConsoleW(hStdErr, L"Debug: ", 7, &written, NULL);
        break;
    case QtWarningMsg:
        WriteConsoleW(hStdErr, L"Warning: ", 9, &written, NULL);
        break;
    case QtCriticalMsg:
        WriteConsoleW(hStdErr, L"Critical: ", 10, &written, NULL);
        break;
    default:
        break;
    }

    WriteConsoleW(hStdErr, wmsg.c_str(), wmsg.length(), &written, NULL);
    WriteConsoleW(hStdErr, L"\n", 1, &written, NULL);

    // 同时输出到调试器（Qt Creator 应用程序输出面板）
    OutputDebugStringW(wmsg.c_str());
    OutputDebugStringW(L"\n");
#else
    // 非 Windows 使用默认行为
    QByteArray localMsg = msg.toLocal8Bit();
    fprintf(stderr, "%s\n", localMsg.constData());
    fflush(stderr);
#endif
}

int main(int argc, char *argv[])
{
#ifdef Q_OS_WIN
    setupUtf8Output();
#endif

    // 安装自定义处理器（关键！）
    qInstallMessageHandler(utf8MessageHandler);

    QApplication a(argc, argv);

    qDebug() << "=== 编码诊断 ===";
    qDebug() << "Qt 版本:" << QT_VERSION_STR;
    qDebug() << "测试中文: 直接UTF-8";
    qDebug() << QStringLiteral("QStringLiteral中文");

    MainWindow mw;
    mw.show();
    return a.exec();
}
