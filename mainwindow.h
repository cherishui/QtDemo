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
class MyThread;

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

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    CMyButton*  Mybtn = nullptr;

    MyThread*  pWorkThread = nullptr;
};
#endif // MAINWINDOW_H
