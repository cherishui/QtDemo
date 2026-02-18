#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QPushButton>
#include <QDebug>

class CMyButton : public QPushButton
{
    Q_OBJECT

public:
    explicit CMyButton(QWidget* parent = nullptr);
    void mousePressEvent(QMouseEvent *event);
};


#endif // MYBUTTON_H
