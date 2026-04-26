#include "cmydateedit.h"
#include <QPainter>
#include <QLineEdit>
#include <QDebug>
#include <QStyle>
#include <QStyleOptionSpinBox>

CMyDateEdit::CMyDateEdit(QWidget *parent)
    : QDateEdit(parent)
    , m_textColor(Qt::red)
    , m_bgColor(Qt::cyan)
    , m_borderColor(Qt::black)
{
    setFrame(false);          // 关闭 QDateEdit 自带边框

    if (lineEdit())
    {
        lineEdit()->setFrame(false);   // 关闭内部 lineEdit 边框
        lineEdit()->setAttribute(Qt::WA_MacShowFocusRect, false);
    }

    UpdateStyle();
}


void CMyDateEdit::SetColors(const QColor& textColor,
                            const QColor& bgColor,
                            const QColor& borderColor)
{
    m_textColor = textColor;
    m_bgColor = bgColor;
    m_borderColor = borderColor;

    UpdateStyle();
}


void CMyDateEdit::UpdateStyle()
{
#ifdef USE_QSS   // 使用QSS設置文字顏色、背景顏色
    QString style = QString(
                        "QDateEdit {"
                        " color:%1;"
                        " background-color:%2;"
                        " border:1px solid %3;"
                        " border-radius:3px;"
                        " padding:2px;"
                        "}"
                        "QDateEdit::drop-down {"
                        " border:none;"
                        "}"
                        )
                        .arg(m_textColor.name())
                        .arg(m_bgColor.name())
                        .arg(m_borderColor.name());

    setStyleSheet(style);
#else   // 自定义paint绘制

    QLineEdit* pEdit = lineEdit();
    if (!pEdit)
        return;

    QPalette pal = pEdit->palette();

    pal.setColor(QPalette::Text, m_textColor);
    pal.setColor(QPalette::Base, m_bgColor);

    pEdit->setPalette(pal);

    update();
#endif
}

#ifndef USE_QSS
void CMyDateEdit::paintEvent(QPaintEvent *event)
{
    // 文字颜色  -> 内部 lineEdit palette
    // 背景颜色  -> 内部 lineEdit palette
    // 边框颜色  -> paintEvent 自绘

    // 先让 Qt 绘制 日期文本\按钮\光标\系统内容
    QDateEdit::paintEvent(event);

    // 自己负责绘制边框
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QRect rc = rect().adjusted(0, 0, -1, -1);

    QColor borderColor = hasFocus()
                             ? QColor(0, 120, 215)
                             : m_borderColor;

    painter.setPen(QPen(borderColor, 1));
    painter.setBrush(Qt::NoBrush);

    painter.drawRoundedRect(rc, 2, 2);
}

void CMyDateEdit::resizeEvent(QResizeEvent *event)
{
    QDateEdit::resizeEvent(event);

    QLineEdit* edit = lineEdit();
    if (!edit)
        return;

    QStyleOptionSpinBox opt;
    initStyleOption(&opt);
    QRect editRect = style()->subControlRect(
        QStyle::CC_SpinBox,
        &opt,
        QStyle::SC_SpinBoxEditField,
        this);
    qDebug() << "inner editRect " << editRect;

    // 只保留左/上/下边框空间，右边贴紧按钮区域
    edit->setGeometry(editRect.adjusted(1, 1, 0, -1));
}
#endif
