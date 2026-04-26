#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "MyButton.h"
#include "WorkThread.h"
#include <QDebug>
#include <QMessageBox>
#include <QThread>
#include <QMouseEvent>
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>

#include "workthread.h"

int g_event_count = 0;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //setWindowFlags(windowFlags() | Qt::FramelessWindowHint);

    // 设置背景颜色和圆角
    // setStyleSheet(R"(
    //     QMainWindow {
    //         background-color: white;
    //         border: 2px solid #cccccc;
    //         border-radius: 15px;
    //     }
    // )");

    qDebug() << ui->m_TopBottomSplitter->orientation();
    qDebug() << ui->m_TopBottomSplitter->opaqueResize();
    qDebug() << ui->m_TopBottomSplitter->handleWidth();
    qDebug() << ui->m_TopBottomSplitter->childrenCollapsible();

    qDebug() << ui->m_LeftRightSplitter;

    qDebug() << "m_LeftRightSplitter->childrenCollapsible" << ui->m_LeftRightSplitter->childrenCollapsible();
    //ui->m_LeftRightSplitter->setCollapsible(0, false);
    //ui->m_LeftRightSplitter->setCollapsible(1, false);
    //qDebug() << ui->m_LeftRightSplitter->isCollapsible(0);
    ui->m_LeftRightSplitter->setChildrenCollapsible(false);
    ui->m_LeftRightSplitter->setMinimumWidth(200);
    ui->m_LeftRightSplitter->setHandleWidth(10);
    ui->m_LeftRightSplitter->setOpaqueResize(true); // 实时预览调整效果

    ui->m_LeftRightSplitter->setStyleSheet(
        "QSplitter::handle {"
        "    background-color: gray;"
        "    border: 1px solid darkgray;"
        "}"
        );

    // 开启鼠标跟踪
    setMouseTracking(true);
    ui->centralwidget->setMouseTracking(true);
    ui->m_TopBottomSplitter->setMouseTracking(true);
    ui->TopWidget->setMouseTracking(true);

    // 启动 Hover 事件
    setAttribute(Qt::WA_Hover);
    installEventFilter(this);
    // 确保中央部件也有Hover
    ui->centralwidget->setAttribute(Qt::WA_Hover);
    ui->centralwidget->installEventFilter(this);

    Mybtn = new CMyButton(this);
    Mybtn->setText("自定义按钮");
    ui->m_LeftRightSplitter->addWidget(Mybtn);

#if 0
    // 窗口的默认上下文策略是 Qt::DefaultContextMenu
    // 作用是在 窗口中按下鼠标右键, qt框架调用 QWidget::contextMenuEvent()
    // 在这里面弹出 QMenu 菜单
    setContextMenuPolicy(Qt::DefaultContextMenu);
#endif

#if 0
    // 该窗口策略 禁用右键菜单
    setContextMenuPolicy(Qt::NoContextMenu);
#endif

#if 0
    // ActionsContextMenu 直接给窗口 addAction 增加右键菜单
    setContextMenuPolicy(Qt::ActionsContextMenu);
    // 给当前窗口添加QAction对象
    QAction* act1  = new QAction("C++");
    QAction* act2 = new QAction("Java");
    QAction* act3  = new QAction("Python");
    this->addAction(act1);
    this->addAction(act2);
    this->addAction(act3);
    connect(act1, &QAction::triggered, this, [=]()
            {
                QMessageBox::information(this, "title", "您选择的是C++...");
            });
#endif


#if 1
    // 策略 Qt::CustomContextMenu
    // 当在窗口中点击鼠标右键, 窗口会发出一个信号: QWidget::customContextMenuRequested()
    // 对应发射出的这个信号, 需要添加一个槽函数, 用来显示右键菜单
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &MainWindow::customContextMenuRequested, this, [=](const QPoint &pos)
            {
                // 参数 pos 是鼠标按下的位置, 但是不能直接使用, 这个坐标不是屏幕坐标, 是当前窗口的坐标
                // 如果要使用这个坐标需要将其转换为屏幕坐标
                QMenu menu;
                QAction* act = menu.addAction("C++");
                connect(act, &QAction::triggered, this, [=]()
                        {
                            QMessageBox::information(this, "title", "您选择的是C++...");
                        });
                menu.addAction("Java");
                menu.addAction("Python");
                // menu.exec(QCursor::pos());
                // 将窗口坐标转换为屏幕坐标
                QPoint newpt = this->mapToGlobal(pos);
                menu.exec(newpt);
            });
#endif

    //Qt::ContextMenuPolicy menuPolicy = contextMenuPolicy();
    //qDebug() << menuPolicy;

    ui->comboBox->addItem("中国");
    ui->comboBox->addItem("美国");
    ui->comboBox->addItem("意大利");
    ui->comboBox->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    qDebug() << "MainWindow 析构开始";

    if (pWorkThread)
    {
        pWorkThread->stopWorkThread();
        delete pWorkThread;
        pWorkThread = nullptr;
    }

    delete ui;
    qDebug() << "MainWindow 析构完成";
}


// 【关键】拦截窗口关闭事件，先安全停止线程
void MainWindow::closeEvent(QCloseEvent *event)
{
    qDebug() << "正在关闭窗口，检查线程状态...";

    if (pWorkThread)
    {
        pWorkThread->stopWorkThread();
        delete pWorkThread;
        pWorkThread = nullptr;
    }

    QMainWindow::closeEvent(event);
}

void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    Q_UNUSED(event);

    // 弹出一个菜单, 菜单项是 QAction 类型
    QMenu menu;
    QAction* act = menu.addAction("C++");
    connect(act, &QAction::triggered, this, [=]()
            {
                QMessageBox::information(this, "title", "您选择的是C++...");
            });
    menu.addAction("Java");
    menu.addAction("Python");
    menu.exec(QCursor::pos());	// 右键菜单被模态显示出来了
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    qDebug() << "MainWindow::mouseMoveEvent" << g_event_count++ <<event;
    QMainWindow::mouseMoveEvent(event);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "MainWindow 收到来自按钮的事件";
    event->accept();

    qDebug() << "MainWindow::mousePressEvent" << g_event_count++ <<event << event->isAccepted();
    QMainWindow::mousePressEvent(event);
}

#include <QHoverEvent>
#include <QObject>
bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    // 只处理发往this的事件，避免递归
    if (obj != this) {
        return QMainWindow::eventFilter(obj, event);
    }

    switch (event->type()) {
    case QEvent::HoverEnter:
        hoverEnterEvent(static_cast<QHoverEvent*>(event));
        return false;  // 继续传递，不要拦截

    case QEvent::HoverLeave:
        hoverLeaveEvent(static_cast<QHoverEvent*>(event));
        return false;

    case QEvent::HoverMove:
        hoverMoveEvent(static_cast<QHoverEvent*>(event));
        return false;  // 返回false让事件继续传递

    default:
        return QMainWindow::eventFilter(obj, event);
    }
}

// ========== HoverMove 处理 ==========
void MainWindow::hoverMoveEvent(QHoverEvent *event)
{
    QPoint pos = event->pos();
    //qDebug() << "HoverMove 悬停移动:" << pos;

    setToolTip(QString("坐标: (%1, %2)").arg(pos.x()).arg(pos.y()));

    event->accept();
    //QMainWindow::hoverMoveEvent(event);
}

// 可选：进入/离开事件（常与Hover配套使用）
void MainWindow::hoverEnterEvent(QHoverEvent *event)  {
    qDebug() << "HoverEnter 鼠标进入主窗口";
    setCursor(Qt::CrossCursor);

    // 【关键】接受事件
    event->accept();

    // 调用基类（重要！）
    //QMainWindow::hoverEnterEvent(event);
}

void MainWindow::hoverLeaveEvent(QHoverEvent *event) {
    qDebug() << "HoverLeave 鼠标离开主窗口";
    unsetCursor();

    event->accept();
    //QMainWindow::hoverLeaveEvent(event);
}


QString func1()
{
    //msleep(10000); // 模拟工作
    qDebug()<<"我是func2函数";
    return "123";
}

QString func2(QString name)
{
    qDebug() << name << "from" << QThread::currentThread();
    return "";
}

#include <iostream>
class A
{
public:
    A()
    {
        qDebug() << "Running in thread:" << QThread::currentThreadId();
        std::cout << "我是 A 的构造函数" << std::endl;
    };

    QString m_func(QString name)
    {
        qDebug() << "Running in thread:" << QThread::currentThreadId();
        m_name = name;
        std::cout << "我是 A 的成员函数" << std::endl;
        return "";
    }
    QString m_name;
};

#include <QtConcurrent>
void MainWindow::on_pushButton_clicked()
{
#if 0
    QFuture<QString> fut1 = QtConcurrent::run(func1);// 1.用QFuture获取该函数的运行结果
    //QFuture<QString> fut2 = QtConcurrent::run(func2, QString("Thread 1"));//2.参数2：向func函数传递的参数
    QString result1 = fut1.result();
    //QString result2 = fut2.result();
    qDebug() << "1. result1" << result1;
    fut1.waitForFinished();
    result1 = fut1.result();
    qDebug() << "2. result1" << result1;
    //fut2.waitForFinished();
#endif

#if 0

#endif
    if (!pWorkThread)
    {
        pWorkThread = new MyThread();
    }

    if (pWorkThread)
    {
        pWorkThread->startWorkThread();
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->label->setText(ui->label->text() + "1");
}


void MainWindow::on_pushButton_3_clicked()
{
    // 创建文本编辑框
    QTextEdit textEdit;
    textEdit.setPlainText("这是要打印的文本内容。");

    // 创建打印机对象
    QPrinter printer;

    // 创建打印对话框并关联打印机对象
    QPrintDialog dialog(&printer);

    // 设置打印对话框的选项
    dialog.setOption(QPrintDialog::PrintSelection, true);

    // 显示打印对话框并等待用户操作
    if (dialog.exec() == QDialog::Accepted) {
        // 用户点击了打印按钮，执行打印操作
        // QPainter painter;
        // painter.begin(&printer);
        // textEdit.print(&painter);
        // painter.end();
    }
}

void MainWindow::on_pushButton_4_clicked()
{

}

