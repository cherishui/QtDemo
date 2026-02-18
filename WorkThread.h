#ifndef WORKTHREAD_H
#define WORKTHREAD_H

#include <QObject>

class WorkThread : public QObject
{
    Q_OBJECT
public:
    explicit WorkThread(QObject* parent = nullptr);
    ~WorkThread();

public slots:
    void doWork();
signals:
    void stopRequested();
    void workFinished();
};

class MyThread : public QObject
{
    Q_OBJECT

public:
    // 开始线程
    void startWorkThread();

    // 停止线程
    void stopWorkThread();

private:
    // 线程相关成员
    QThread* m_workerThread = nullptr;  // 使用成员变量便于管理
    WorkThread* m_worker = nullptr;
    bool m_isClosing = false;  // 标记是否正在关闭
};


#endif // WORKTHREAD_H
