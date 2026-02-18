#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QThread>
#include <QPushButton>
#include <QMouseEvent>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class CMyButton;

class WorkThread : public QObject
{
    Q_OBJECT
public:
    explicit WorkThread(QObject* parent = nullptr)
        : QObject(parent)
    {}

    ~WorkThread();
public slots:
    void doWork();
signals:
    void stopRequested();
    void workFinished();
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;  // 拦截关闭事件

    void contextMenuEvent(QContextMenuEvent* event);
    void mouseMoveEvent(QMouseEvent* event) override;

    void mousePressEvent(QMouseEvent* event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;

    void hoverMoveEvent(QHoverEvent *event);
    void hoverLeaveEvent(QHoverEvent *event);
    void hoverEnterEvent(QHoverEvent *event);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void stopWorkThread();


private:
    Ui::MainWindow *ui;
    CMyButton*  Mybtn = nullptr;

    // 线程相关成员
    QThread* m_workerThread = nullptr;  // 使用成员变量便于管理
    WorkThread* m_worker = nullptr;
    bool m_isClosing = false;  // 标记是否正在关闭


};
#endif // MAINWINDOW_H
