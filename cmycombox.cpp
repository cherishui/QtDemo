#include "cmycombox.h"
#include <QPainter>
#include <QAbstractItemView>
#include <QLineEdit>

// 构造函数，初始化颜色并设置为可编辑模式
CMyCombox::CMyCombox(QWidget* parent) : QComboBox(parent)
    , m_textColor(Qt::black)
    , m_backgroundColor(Qt::yellow)
    , m_borderColor(Qt::gray)
    , m_arrowColor(Qt::green)
    , m_popupBackgroundColor(Qt::yellow)
    , m_editBackgroundColor(Qt::red)
    , m_arrowBackgroundColor(Qt::blue)
{
    setEditable(true);
    setEditBackgroundColor(m_editBackgroundColor);
    // 初始化QLineEdit几何，为右侧箭头区预留空间
    if (lineEdit()) {
        int arrowAreaWidth = 20;
        QRect editRect = rect().adjusted(2, 2, -arrowAreaWidth, -2);
        lineEdit()->setGeometry(editRect);
    }
}


// 设置文字颜色
void CMyCombox::setTextColor(const QColor& color)
{
    m_textColor = color;
    update();
}

// 设置主背景颜色
void CMyCombox::setBackgroundColor(const QColor& color)
{
    m_backgroundColor = color;
    update();
}

// 设置边框颜色
void CMyCombox::setBorderColor(const QColor& color)
{
    m_borderColor = color;
    update();
}

// 设置下拉箭头颜色
void CMyCombox::setArrowColor(const QColor& color)
{
    m_arrowColor = color;
    update();
}

// 设置下拉框背景颜色
void CMyCombox::setPopupBackgroundColor(const QColor& color)
{
    m_popupBackgroundColor = color;
}

// 设置编辑区背景颜色
void CMyCombox::setEditBackgroundColor(const QColor& color)
{
    m_editBackgroundColor = color;
    if (isEditable() && lineEdit()) {
        QPalette p = lineEdit()->palette();
        p.setColor(QPalette::Base, m_editBackgroundColor);
        lineEdit()->setPalette(p);
        lineEdit()->update();
    }
    update();
}

// 设置箭头区域背景颜色
void CMyCombox::setArrowBackgroundColor(const QColor& color)
{
    m_arrowBackgroundColor = color;
    update();
}

// 重绘控件，包括背景、边框、箭头区、文本和箭头
void CMyCombox::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 绘制主背景
    painter.setBrush(m_backgroundColor);
    painter.setPen(Qt::NoPen);
    painter.drawRect(rect());

    // 绘制边框
    painter.setPen(QPen(m_borderColor, 1));
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(rect().adjusted(0, 0, -1, -1));

    // 绘制文本（仅非可编辑模式）
    if (!isEditable()) {
        painter.setPen(m_textColor);
        QRect textRect = rect().adjusted(4, 0, -24, 0);
        QString text = currentText();
        painter.drawText(textRect, Qt::AlignVCenter | Qt::AlignLeft, text);
    }

    // 绘制下拉箭头
    int arrowW = 12, arrowH = 8;
    int x = width() - arrowW - 8;
    int y = (height() - arrowH) / 2;
    QPolygon arrow;
    arrow << QPoint(x, y)
          << QPoint(x + arrowW, y)
          << QPoint(x + arrowW / 2, y + arrowH);
    painter.setBrush(m_arrowColor);
    painter.setPen(Qt::NoPen);
    painter.drawPolygon(arrow);

    // 绘制箭头区域背景（最后绘制，确保不被其他内容覆盖）
    int arrowAreaWidth = 20;
    QRect arrowBgRect(width() - arrowAreaWidth, 0, arrowAreaWidth, height());
    painter.setBrush(m_arrowBackgroundColor);
    painter.setPen(Qt::NoPen);
    painter.drawRect(arrowBgRect);

    // 重新绘制箭头以确保其在背景上方
    painter.setBrush(m_arrowColor);
    painter.setPen(Qt::NoPen);
    painter.drawPolygon(arrow);
}

// 显示下拉框，并设置下拉框背景色
void CMyCombox::showPopup()
{
    QComboBox::showPopup();
    if (view()) {
        view()->setStyleSheet(QString("QListView { background: %1; }").arg(m_popupBackgroundColor.name()));
    }
}

// 重载resizeEvent，确保控件大小改变时QLineEdit几何同步更新
void CMyCombox::resizeEvent(QResizeEvent* event)
{
    QComboBox::resizeEvent(event);
    if (isEditable() && lineEdit()) {
        // 调整QLineEdit的几何，为右侧箭头区预留空间
        int arrowAreaWidth = 20;
        QRect editRect = rect().adjusted(2, 2, -arrowAreaWidth, -2);
        lineEdit()->setGeometry(editRect);
    }
}
