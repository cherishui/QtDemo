#include "WorkThread.h"

#include <QDebug>
#include <QThread>
#include <QMessageBox>
WorkThread::WorkThread(QObject *parent)
    : QObject{parent}
{}


WorkThread::~WorkThread() {
    qDebug() << "WorkThread 销毁";
}

void WorkThread::doWork()
{
    for (int i = 0; i < 100; i++) {
        if (QThread::currentThread()->isInterruptionRequested() ||
            QThread::currentThread()->isFinished()) {
            qDebug() << "线程被要求退出...";
            break;
        }

        qDebug() << "start thread run:" << i;

        QThread::msleep(100);  // 100ms 检查一次，响应更快

        qDebug() << "end thread run:" << i;
    }

    qDebug() << "before thread workFinished:";
    emit workFinished();
    qDebug() << "after thread workFinished:";
}

void MyThread::startWorkThread()
{
    // 如果已有线程在运行，先停止
    if (m_workerThread && m_workerThread->isRunning()) {
        QMessageBox::warning(nullptr, "警告", "线程已在运行中！");
        return;
    }

    // 清理旧对象（如果存在）
    // 清理旧对象
    stopWorkThread();

    // 基于 QObject 创建一个工作者类
    // 新建一个 QThread 和 上面的工作线程类，调用 QObject::moveToThread
    // 将工作者移动到线程运行
    m_workerThread = new QThread(); // 都不设置parent，手动管理
    m_worker = new WorkThread(); // 工作者类不指定父对象，通过信号槽自动删除
    m_worker->moveToThread(m_workerThread);  // 移动到线程

    // 先调用 moveToThread，后调用 connect 连接，这个时候不需要指明第五个参数
    // 如果 先调用 connect ，后再调用 moveToThread ，这会表示 DirectConnection，逻辑错误。
    // 推荐写法：依赖 AutoConnection，但确保 moveToThread 在 connect 之前
    // 【关键】只使用 DirectConnection 或 QueuedConnection，避免 AutoConnection 歧义
    connect(m_workerThread, &QThread::started,
            m_worker, &WorkThread::doWork,
            Qt::QueuedConnection);

    // 工作完成 -> 线程退出（QueuedConnection 确保跨线程安全）
    connect(m_worker, &WorkThread::workFinished,
            m_workerThread, &QThread::quit,
            Qt::QueuedConnection);

    // 5. 启动
    m_workerThread->start();
}

// 安全停止线程的封装函数
void MyThread::stopWorkThread()
{
    if (!m_workerThread) return;

    if (m_workerThread->isRunning()) {
        m_isClosing = true;
        qDebug() << "请求线程中断...";

        // 通知 worker 和线程退出
        if (m_worker) {
            emit m_worker->stopRequested();
        }
        m_workerThread->requestInterruption();
        m_workerThread->quit();  // 必须调用，让事件循环处理 deleteLater
    }

    // 等待线程结束（非阻塞式检查）
    if (m_workerThread->isRunning()) {
        if (!m_workerThread->wait(3000)) {
            qWarning() << "线程未能优雅退出，强制终止";
            m_workerThread->terminate();
            m_workerThread->wait(1000);
        }
    }

    // 手动清理资源
    // 【关键】先断开所有信号槽连接，防止野指针访问！
    if (m_worker) {
        m_worker->disconnect();  // 断开 worker 的所有信号槽
        delete m_worker;
        m_worker = nullptr;
    }
    if (m_workerThread) {
        m_workerThread->disconnect();  // 断开线程的所有信号槽
        delete m_workerThread;
        m_workerThread = nullptr;
    }

    qDebug() << "线程资源已清理";
}
