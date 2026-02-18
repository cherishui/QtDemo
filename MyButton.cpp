#include "MyButton.h"
#include <QMouseEvent>

void CMyButton::mousePressEvent(QMouseEvent *event)
{
#if 0
        event->ignore();  // 我不处理，传给父组件

        qDebug() << "MyButton 收到点击，但 ignore，准备传给父组件";
#else
    qDebug() << "CMyButton::mousePressEvent" << event << event->isAccepted();

    event->accept();  // 我处理了，不传给父组件

    qDebug() << "MyButton 处理点击，事件到此结束";
#endif
    // 调用父类，让 QPushButton 处理按钮的按下效果、发射 clicked() 信号等
    QPushButton::mousePressEvent(event);

    // 注意：父类通常会调用 event->accept()，所以这里不需要再调用
}

CMyButton::CMyButton(QWidget *parent)
    :QPushButton(parent)
{

}
